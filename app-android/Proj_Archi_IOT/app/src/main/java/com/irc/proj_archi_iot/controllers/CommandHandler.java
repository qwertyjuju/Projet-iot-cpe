package com.irc.proj_archi_iot.controllers;


import static com.irc.proj_archi_iot.utils.JsonUtils.deserializeMeasurement;

import android.util.Log;

import com.irc.proj_archi_iot.models.Device;
import com.irc.proj_archi_iot.repositories.MeasureRepository;
import com.irc.proj_archi_iot.services.UdpService;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

public class CommandHandler {

    private static CommandHandler instance;
    private CommandHandler() {
        udpService = UdpService.getInstance();
    }
    public static CommandHandler getInstance() {
        if (instance == null) instance = new CommandHandler();
        return instance;
    }

    private final UdpService udpService;

    public interface ConnectionCallback {
        void onConnectionResult(boolean connectionStatus);
    }

    public void connectToServer(String ip, int port, ConnectionCallback callback) {
        udpService.connect(ip, port, callback);
    }

    public void getDevices() {
        sendCommand("get-devices", null);
    }

    public void getMeasures(String deviceId) {
        sendCommand("get-measures", deviceId);
    }

    public void getMeasure(String deviceId) {
        sendCommand("get-measure", deviceId);
    }

    public void setOrder(String deviceId, String order) {
        sendCommand("set-order", deviceId, order);
    }

    private void sendCommand(String cmd, String... args) {
        JSONObject jsonCommand = new JSONObject();
        try {
            jsonCommand.put("cmd", cmd);
            JSONArray argsArray = new JSONArray();
            if (args != null && args.length > 0) {
                for (String arg : args) {
                    argsArray.put(arg);
                }
            }
            jsonCommand.put("args", argsArray);
        } catch (JSONException e) {
            throw new RuntimeException(e);
        }
        udpService.sendCommand(jsonCommand.toString());
    }

    /*

    public void connectToServer(String ip, int port, UdpService.ConnectionCallback callback) {
        udpService.connect(ip, port, callback);
    }

    public void getDevices() {

        udpService.sendCommand("get-devices", new UdpService.ResponseCallback() {
            @Override
            public void onResponseReceived(String response) {
                try {
                    JSONArray deviceIds = new JSONArray(response);

                    for (int i = 0; i < deviceIds.length(); i++) {
                        MeasureRepository
                                .getInstance()
                                .addDevice(new Device(deviceIds.get(i).toString(), "placeholder"));
                    }
                } catch (JSONException e) {
                    Log.e("Command get-devices", "Error while serializing response", e);
                }
            }

            @Override
            public void onError(Exception e) {
                Log.e("Command get-devices", "Error while executing command", e);
            }
        });
    }

    public void getMeasures(String deviceId) {
        String command = "get-measures " + deviceId;

        networkService.sendCommand(command, new NetworkService.ResponseCallback() {
            @Override
            public void onResponseReceived(String response) {
                try {
                    JSONArray measures = new JSONArray(response);

                    for (int i = 0; i < measures.length(); i++) {
                        MeasureRepository
                                .getInstance()
                                .addMeasureToDevice(deviceId, deserializeMeasurement((JSONObject)measures.get(i)));
                    }
                } catch (JSONException e) {
                    Log.e("Command get-measures", "Error while serializing response");
                }
            }

            @Override
            public void onError(Exception e) {
                Log.e("Command get-measures", "Error while executing command", e);
            }
        });
    }

    public void getMeasure(String deviceId) {
        String command = "get-measure " + deviceId;

        networkService.sendCommand(command, new NetworkService.ResponseCallback() {
            @Override
            public void onResponseReceived(String response) {
                try {
                    Log.d("command response callback", response);
                    JSONObject measure = new JSONObject(response);

                    MeasureRepository
                            .getInstance()
                            .addMeasureToDevice(deviceId, deserializeMeasurement(measure));
                } catch (JSONException e) {
                    Log.e("Command get-measures", "Error while serializing response");
                }
            }

            @Override
            public void onError(Exception e) {
                Log.e("Command get-measures", "Error while executing command", e);
            }
        });
    }
    */
}
