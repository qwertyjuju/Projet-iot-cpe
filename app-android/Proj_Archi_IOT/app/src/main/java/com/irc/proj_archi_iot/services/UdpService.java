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

/**
 * Service pour la réception et l'envoi de messages UDP.
 */
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

    /**
     * Instance unique du service UDP (singleton).
     */
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

    /**
     * Connecte au serveur UDP.
     * @param ip Adresse IP du serveur
     * @param port Port du serveur
     * @param callback Callback pour la réception du résultat de la connexion
     */
    public void connect(String ip, int port, CommandHandler.ConnectionCallback callback) {
        try {
            // Vérification de l'adresse IP
            distIp = InetAddress.getByName(ip);
            distPort = port;

            // Envoi d'une demande de synchronisation (SYN) au serveur
            sendCommand("SYN");

            // Attente de la réponse SYN-ACK du serveur pour notifier au callback
            handler.postDelayed(() -> callback.onConnectionResult(isConnected), 2000);

        } catch (UnknownHostException e) {
            Log.e("UdpService", "Unknown host exception", e);
            handler.post(() -> callback.onConnectionResult(false));
        }
    }

    /**
     * Envoie une commande UDP.
     * @param command Commande à envoyer
     */
    public void sendCommand(String command) {
        // Lock pour accéder à la queue d'envoi
        sendLock.lock();
        try {
            // Enreigstrement de la commande dans la queue d'envoi
            sendQueue.offer(command);
            startSendThread();
        } finally {
            // Déverrouillage du lock
            sendLock.unlock();
        }
    }

    /**
     * Lance un thread pour l'envoi des commandes UDP.
     */
    private void startSendThread() {

        // Lancement du thread pour l'envoi des commandes UDP
        sendExecutor.execute(() -> {

            // Tant qu'il y a des commandes à envoyer, on envoie une par une
            while (!sendQueue.isEmpty()) {

                // Lock pour accéder à la queue d'envoi
                sendLock.lock();
                try {

                    // Récupération de la commande à envoyer
                    String command = sendQueue.poll();

                    // Envoi de la commande au serveur
                    if (command != null) send(command);
                } finally {
                    // Déverrouillage du lock
                    sendLock.unlock();
                }
            }
        });
    }

    /**
     * Lance un thread pour la réception des messages UDP.
     */
    private void startReceiveThread() {

        // Lancement du thread pour la réception des messages UDP
        receiveExecutor.execute(() -> {

            while (true) {

                // Récupération du message reçu
                String response = receive();

                // Si le message est vide, on continue à attendre
                if (response == null) continue;

                // Lock pour accéder à la queue de réception
                receiveLock.lock();
                try {
                    // Enregistrement du message dans la queue de réception
                    receiveQueue.offer(response);

                    // Traitement du message reçu
                    handleReceivedMessage(response);
                } finally {
                    // Déverrouillage du lock
                    receiveLock.unlock();
                }
            }
        });
    }

    /**
     * Appelle le gestionnaire de réponse pour le message reçu.
     * @param response
     */
    private void handleReceivedMessage(String response) {
        if (response.equals("SYN_ACK")) {
            // Si le message est une réponse SYN-ACK, on active la connexion et on envoie un ACK
            isConnected = true;
            sendCommand("ACK");
        }
        else {
            // Sinon, on appelle le gestionnaire de réponse pour traiter le message reçu
            ResponseHandler.getInstance().handle(response);
        }
    }

    /**
     * Envoie un message UDP.
     * @param msg Message
     */
    private void send(String msg) {
        try {
            // Construction du paquet UDP avec le message et l'adresse du serveur
            byte[] buffer = msg.getBytes();
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length, distIp, distPort);

            // Envoi du paquet UDP au serveur
            socket.send(packet);

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * Récupère un message UDP reçu.
     * @return Message reçu ou null si aucun message n'est disponible sur le socket
     */
    private String receive() {
        // Construction du paquet UDP pour la réception du message
        byte[] buffer = new byte[BUFFER_SIZE];
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
        try {
            // Réception du paquet UDP du serveur
            socket.receive(packet);

            // Retourne le message reçu converti en chaîne de caractères
            return new String(packet.getData(), 0, packet.getLength());
        } catch (IOException ignore) {

        }
        return null;
    }
}
