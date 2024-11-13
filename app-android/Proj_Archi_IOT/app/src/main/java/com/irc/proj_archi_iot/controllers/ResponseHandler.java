package com.irc.proj_archi_iot.controllers;

import com.irc.proj_archi_iot.models.Device;
import com.irc.proj_archi_iot.models.ReceivedMeasurement;
import com.irc.proj_archi_iot.repositories.MeasureRepository;
import com.irc.proj_archi_iot.utils.JsonUtils;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * Classe pour gérer les réponses reçues du serveur
 */
public class ResponseHandler {

    private final MeasureRepository repository;

    // Initialisation de la classe en singleton
    private static ResponseHandler instance;
    private ResponseHandler() { repository = MeasureRepository.getInstance(); }
    public static ResponseHandler getInstance() {
        if (instance == null) instance = new ResponseHandler();
        return instance;
    }

    /**
     * Traite les réponses reçues du serveur
     * @param jsonResponse réponse du serveur
     */
    public void handle(String jsonResponse) {
        try {
            // Parsing du JSON reçu
            JSONObject jsonObject = new JSONObject(jsonResponse);

            // Récupération de la commande et des arguments
            String cmdStr = jsonObject.getString("cmd");
            JSONArray argsArray = jsonObject.getJSONArray("args");

            // Traitement des arguments selon la commande
            switch (cmdStr) {
                case "set-devices": setDevices(argsArray); break;
                case "set-measures": setMeasurements(argsArray); break;
                case "set-measure": setMeasurement(argsArray); break;
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    /**
     * Ajout des périphériques au repository
     * @param args arguments de la commande
     * @throws JSONException si le parsing du JSON échoue
     */
    private void setDevices(JSONArray args) throws JSONException {
        for (int i = 0; i < args.length(); i++) {
            repository.addDevice(new Device(args.getString(i), "")); // nom vide pour le moment, peut être remplacé prochainement par le nom du lieu de mesure etc..
        }
    }

    /**
     * Ajout des mesures à un périphérique dans le repository
     * @param args arguments de la commande
     * @throws JSONException si le parsing du JSON échoue
     */
    private void setMeasurements(JSONArray args) throws JSONException {
        JSONObject response = args.getJSONObject(0);

        // Récupération de l'id du périphérique sur lequel ajouter les mesures
        String deviceId = response.getString("device_id");

        // Récupération des mesures pour ce périphérique
        JSONArray measurementsArray = response.getJSONArray("measures");

        // Pour chaque mesure, on ajoute la mesure au repository du périphérique correspondant
        for (int i = 0; i < measurementsArray.length(); i++) {
            JSONObject measurementJson = measurementsArray.getJSONObject(i);
            JSONObject dataObject = measurementJson.getJSONObject("measure");
            String timestamp = measurementJson.getString("measure_timestamp");
            repository.addMeasureToDevice(deviceId, JsonUtils.deserializeMeasurement(dataObject, timestamp));
        }
    }

    /**
     * Ajout d'une mesure à un périphérique dans le repository
     * @param args arguments de la commande
     * @throws JSONException si le parsing du JSON échoue
     */
    private void setMeasurement(JSONArray args) throws JSONException {
        JSONObject response = args.getJSONObject(0);

        // Récupération de l'id du périphérique sur lequel ajouter la mesure
        String deviceId = response.getString("device_id");

        // Récupération de la mesure pour ce périphérique
        JSONObject measurementJson = response.getJSONObject("last_measure");
        String timestamp = response.getString("measure_timestamp");

        // On ajoute la mesure au repository du périphérique correspondant
        repository.addMeasureToDevice(deviceId, JsonUtils.deserializeMeasurement(measurementJson, timestamp));
    }
}
