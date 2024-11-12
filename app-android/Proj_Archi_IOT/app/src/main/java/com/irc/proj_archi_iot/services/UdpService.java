package com.irc.proj_archi_iot.services;

import android.app.Service;
import android.content.Intent;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.util.Log;

import com.irc.proj_archi_iot.controllers.CommandHandler;
import com.irc.proj_archi_iot.controllers.ResponseHandler;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.concurrent.BlockingDeque;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.locks.ReentrantLock;

public class UdpService {
    private final ExecutorService sendExecutor;
    private final ExecutorService receiveExecutor;
    private final BlockingQueue<String> sendQueue;
    private final BlockingQueue<String> receiveQueue;
    private final ReentrantLock sendLock = new ReentrantLock();
    private final ReentrantLock receiveLock = new ReentrantLock();

    private DatagramSocket socket;

    private boolean isConnected = false;

    private InetAddress distIp;
    private int distPort;

    private final int LOCAL_PORT = 10000;
    private final int BUFFER_SIZE = 4096;
    private final int QUEUE_SIZE = 10;

    private final Handler handler;

    private static UdpService instance = null;
    private UdpService() {
        handler = new Handler(Looper.getMainLooper());
        sendQueue = new LinkedBlockingQueue<>(QUEUE_SIZE);
        receiveQueue = new LinkedBlockingQueue<>(QUEUE_SIZE);
        sendExecutor = Executors.newSingleThreadExecutor();
        receiveExecutor = Executors.newSingleThreadExecutor();
        try {
            socket = new DatagramSocket(LOCAL_PORT);
            socket.setSoTimeout(10000);
        } catch (SocketException e) {
            Log.e("NetworkService", "Failed to init socket", e);
        }
        startReceiveThread();
    }
    public static UdpService getInstance() {
        if (instance == null) instance = new UdpService();
        return instance;
    }

    public void connect(String ip, int port, CommandHandler.ConnectionCallback callback) {
        try {
            distIp = InetAddress.getByName(ip);
            distPort = port;

            sendCommand("SYN");

            handler.postDelayed(() -> callback.onConnectionResult(isConnected), 2000);

        } catch (UnknownHostException e) {
            Log.e("UdpService", "Unknown host exception", e);
            handler.post(() -> callback.onConnectionResult(false));
        }
    }

    public void sendCommand(String command) {
        sendLock.lock();
        try {
            sendQueue.offer(command);
            startSendThread();
        } finally {
            sendLock.unlock();
        }
    }

    private void startSendThread() {
        sendExecutor.execute(() -> {
            while (!sendQueue.isEmpty()) {
                sendLock.lock();
                try {
                    String command = sendQueue.poll();
                    if (command != null) send(command);
                } finally {
                    sendLock.unlock();
                }
            }
        });
    }

    private void startReceiveThread() {
        receiveExecutor.execute(() -> {
            while (true) {
                String response = receive();
                if (response == null) continue;
                receiveLock.lock();
                try {
                    receiveQueue.offer(response);
                    handleReceivedMessage(response);
                } finally {
                    receiveLock.unlock();
                }
            }
        });
    }

    private void handleReceivedMessage(String response) {
        if (response.equals("SYN_ACK")) {
            isConnected = true;
            sendCommand("ACK");
        }
        else {
            ResponseHandler.getInstance().handle(response);
        }
    }

    private void send(String msg) {
        try {
            byte[] buffer = msg.getBytes();
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length, distIp, distPort);
            socket.send(packet);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private String receive() {
        byte[] buffer = new byte[BUFFER_SIZE];
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
        try {
            socket.receive(packet);
            return new String(packet.getData(), 0, packet.getLength());
        } catch (IOException ignore) {

        }
        return null;
    }
}
