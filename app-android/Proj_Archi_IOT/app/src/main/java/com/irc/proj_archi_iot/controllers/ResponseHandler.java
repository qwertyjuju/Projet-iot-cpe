package com.irc.proj_archi_iot.controllers;

import com.irc.proj_archi_iot.models.Device;
import com.irc.proj_archi_iot.models.ReceivedMeasurement;
import com.irc.proj_archi_iot.repositories.MeasureRepository;
import com.irc.proj_archi_iot.utils.JsonUtils;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class ResponseHandler {

    private final MeasureRepository repository;

    private static ResponseHandler instance;
    private ResponseHandler() { repository = MeasureRepository.getInstance(); }
    public static ResponseHandler getInstance() {
        if (instance == null) instance = new ResponseHandler();
        return instance;
    }

    public void handle(String jsonResponse) {
        try {
            JSONObject jsonObject = new JSONObject(jsonResponse);

            String cmdStr = jsonObject.getString("cmd");
            JSONArray argsArray = jsonObject.getJSONArray("args");

            switch (cmdStr) {
                case "set-devices": setDevices(argsArray); break;
                case "set-measures": setMeasurements(argsArray); break;
                case "set-measure": setMeasurement(argsArray); break;
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    private void setDevices(JSONArray args) throws JSONException {
        for (int i = 0; i < args.length(); i++) {
            repository.addDevice(new Device(args.getString(i), ""));
        }
    }

    private void setMeasurements(JSONArray args) throws JSONException {
        JSONObject response = args.getJSONObject(0);

        String deviceId = response.getString("device_id");
        JSONArray measurementsArray = response.getJSONArray("measures");

        for (int i = 0; i < measurementsArray.length(); i++) {
            JSONObject measurementJson = measurementsArray.getJSONObject(i);
            repository.addMeasureToDevice(deviceId, JsonUtils.deserializeMeasurement(measurementJson));
        }
    }

    private void setMeasurement(JSONArray args) throws JSONException {
        JSONObject response = args.getJSONObject(0);

        String deviceId = response.getString("device_id");
        JSONObject measurementJson = response.getJSONObject("last_measure");
        repository.addMeasureToDevice(deviceId, JsonUtils.deserializeMeasurement(measurementJson));
    }
}
