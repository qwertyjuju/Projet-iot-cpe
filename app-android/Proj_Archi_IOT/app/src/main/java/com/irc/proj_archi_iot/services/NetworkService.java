package com.irc.proj_archi_iot.services;

import android.os.Handler;
import android.os.Looper;
import android.util.Log;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.CountDownLatch;

public class NetworkService {
    private InetAddress serverAddress;
    private int serverPort;
    private DatagramSocket socket;

    private boolean isConnected = false;
    private final Handler handler;
    private static final int BUFFER_SIZE = 2048;
    private static final int LOCAL_PORT = 10000;

    private static NetworkService instance = null;
    private NetworkService() {
        handler = new Handler(Looper.getMainLooper());
        try {
            socket = new DatagramSocket(LOCAL_PORT);
            socket.setSoTimeout(10000);
        } catch (SocketException e) {
            Log.e("NetworkService", "Failed to init socket", e);
        }
    }
    public static NetworkService getInstance() {
        if (instance == null) instance = new NetworkService();
        return instance;
    }

    public void connect(String ip, int port, ConnectionCallback callback) {
        disconnect();
        CompletableFuture.runAsync(() -> {
            try {
                serverAddress = InetAddress.getByName(ip);
                serverPort = port;
                socket = new DatagramSocket();

                byte[] synBuffer = "SYN".getBytes();
                DatagramPacket synPacket = new DatagramPacket(synBuffer, synBuffer.length, serverAddress, serverPort);
                socket.send(synPacket);

                byte[] responseBuffer = new byte[BUFFER_SIZE];
                DatagramPacket responsePacket = new DatagramPacket(responseBuffer, responseBuffer.length);
                socket.receive(responsePacket);
                String response = new String(responsePacket.getData(), 0, responsePacket.getLength());
                boolean connectionSuccess = response.equals("SYN_ACK");

                byte[] ackBuffer = "ACK".getBytes();
                DatagramPacket ackPacket = new DatagramPacket(ackBuffer, ackBuffer.length, serverAddress, serverPort);
                socket.send(ackPacket);

                isConnected = connectionSuccess;
                handler.post(() -> callback.onConnectionResult(connectionSuccess));

            } catch (IOException e) {
                handler.post(() -> callback.onConnectionResult(false));
            }
        });
    }

    private final Object lock = new Object();

    public void sendCommand(String command, ResponseCallback callback) {
        if (!isConnected) return;
        CompletableFuture.runAsync(() -> {
            synchronized (lock) {
                try {
                    byte[] buffer = command.getBytes();
                    DatagramPacket packet = new DatagramPacket(buffer, buffer.length, serverAddress, serverPort);
                    socket.send(packet);

                    byte[] responseBuffer = new byte[BUFFER_SIZE];
                    DatagramPacket responsePacket = new DatagramPacket(responseBuffer, responseBuffer.length);
                    socket.receive(responsePacket);

                    String response = new String(responsePacket.getData(), 0, responsePacket.getLength());
                    handler.post(() -> callback.onResponseReceived(response));
                    Log.d("Command sender", response);

                } catch (IOException e) {
                    Log.e("NetworkService", "Error processing command", e);
                    handler.post(() -> callback.onError(e));
                }
            }
        });
    }

    public void disconnect() {
        try {
            if (socket != null && !socket.isClosed()) {
                socket.close();
                isConnected = false;
            }
        } catch (Exception e) {
            Log.e("DisconnectError", "Failed to disconnect", e);
        }
    }

    public interface ConnectionCallback {
        void onConnectionResult(boolean result);
    }

    public interface ResponseCallback {
        void onResponseReceived(String response);
        void onError(Exception e);
    }
}
