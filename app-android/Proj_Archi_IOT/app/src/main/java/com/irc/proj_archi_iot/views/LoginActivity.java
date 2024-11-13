package com.irc.proj_archi_iot.views;

import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.irc.proj_archi_iot.controllers.CommandHandler;
import com.irc.proj_archi_iot.R;

import java.util.regex.Pattern;

public class LoginActivity extends AppCompatActivity {

    // Elements de l'UI
    private EditText fieldIp, fieldPort;
    private Button btnConnect;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_login);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.login), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        // Initialisation de l'UI
        initUI();

        // Configuration des gestionnaires d'événements
        setupEventListeners();
    }

    /**
     * Initialise l'UI et associe les champs d'entrée et le bouton.
     */
    private void initUI() {
        fieldIp = findViewById(R.id.field_server_ip);
        fieldPort = findViewById(R.id.field_server_port);
        btnConnect = findViewById(R.id.btn_server_connect);
    }

    /**
     * Configure les gestionnaires d'événements pour les boutons.
     */
    private void setupEventListeners() {
        btnConnect.setOnClickListener(v -> tryConnection());
    }

    /**
     * Essaie d'établir une connexion au serveur en utilisant les entrées IP et port.
     */
    private void tryConnection() {
        if (!validateInput()) {
            return;
        }

        String ip = fieldIp.getText().toString();
        int port = Integer.parseInt(fieldPort.getText().toString());

        CommandHandler.getInstance().connectToServer(ip, port, this::startMainActivity);
    }

    /**
     * Valide les entrées IP et port saisies par l'utilisateur.
     *
     * @return true si les entrées sont valides, false sinon.
     */
    private boolean validateInput() {
        String ipPattern = "^((25[0-5]|2[0-4][0-9]|[0-1]?[0-9]{1,2})\\.){3}(25[0-5]|2[0-4][0-9]|[0-1]?[0-9]{1,2})$";
        String ipAddress = fieldIp.getText().toString().trim();
        String portStr = fieldPort.getText().toString().trim();

        if (TextUtils.isEmpty(ipAddress) || !Pattern.matches(ipPattern, ipAddress)) {
            fieldIp.setError("Please enter a valid IP address");
            return false;
        }

        int port;
        try {
            port = Integer.parseInt(portStr);
            if (port < 1 || port > 65535) {
                fieldPort.setError("Please enter a valid port (1-65535)");
                return false;
            }
        } catch (NumberFormatException e) {
            fieldPort.setError("Port must be a number");
            return false;
        }

        return true;
    }

    /**
     * Lance l'activité principale si la connexion est établie, sinon affiche un message d'erreur.
     *
     * @param isConnected Booléen indiquant l'état de la connexion.
     */
    private void startMainActivity(boolean isConnected) {
        if (isConnected) {
            CommandHandler.getInstance().getDevices();
            Intent intent = new Intent(this, MainActivity.class);
            startActivity(intent);
        } else {
            Toast.makeText(this, "Connection failure", Toast.LENGTH_SHORT).show();
        }
    }
}
