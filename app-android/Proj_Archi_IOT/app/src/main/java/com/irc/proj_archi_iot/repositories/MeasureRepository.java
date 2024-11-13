package com.irc.proj_archi_iot.repositories;

import android.os.Build;
import android.util.Log;

import com.irc.proj_archi_iot.models.Device;
import com.irc.proj_archi_iot.models.Measure;
import com.irc.proj_archi_iot.models.MeasureType;
import com.irc.proj_archi_iot.models.ReceivedMeasurement;

import java.time.Instant;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.chrono.ChronoLocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Classe singleton de stockage des mesures.
 */
public class MeasureRepository {

    // Initalisation de la casse en singleton
    private static final MeasureRepository instance = new MeasureRepository();
    private MeasureRepository() {}
    public static MeasureRepository getInstance() { return instance; }

    // Les mesures sont stockées dans le pétiphérique associé
    private final List<Device> devices = new ArrayList();

    /**
     * Ajoute un péripérique au registre.
     * @param device périphérique à ajouter
     */
    public void addDevice(Device device) {
        devices.add(device);
    }

    /**
     * Ajoute une mesure au péripérique spécifié.
     * @param deviceId ID du péripérique
     * @param measure Mesure à ajouter
     */
    public void addMeasureToDevice(String deviceId, ReceivedMeasurement measure) {
        for (int i = 0; i < devices.size(); i++) {
            if (devices.get(i).id.equals(deviceId)) {
                devices.get(i).measures.add(measure);
            }
        }
    }

    /**
     * Récupère la plus récente mesure d'un péripérique
     * @param deviceId id du péripérique
     * @return la mesure la plus récente pour le péripérique, ou null si aucune mesure n'est disponible
     */
    public ReceivedMeasurement getLatestMeasureForDevice(String deviceId) {
        List<ReceivedMeasurement> measures = getMeasuresForDevice(deviceId);
        if (measures.isEmpty()) return null;
        ReceivedMeasurement latestMeasure = measures.get(0);

        // Trouve la mesure la plus récente selon le timestamp
        for (ReceivedMeasurement measure : measures) {
            // Utilisation du DateTimeFormatter pour la comparaison des timestamps
            if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
                DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss.SSSSSS");
                if (LocalDateTime.parse(measure.datetime, formatter).isAfter(LocalDateTime.parse(latestMeasure.datetime, formatter))) {
                    latestMeasure = measure;
                }
            }
            else {
                Log.e("Repo", "SDK version not API ok blbl"); // Message d'erreur nul, là j'ai eu la flemme
            }
        }
        return latestMeasure;
    }

    /**
     * Récupère toutes les mesures d'un péripérique
     * @param deviceId id du péripérique
     * @return toutes les mesures pour le péripérique, ou une liste vide si aucune mesure n'est disponible
     */
    public List<ReceivedMeasurement> getMeasuresForDevice(String deviceId) {
        for (Device d : devices) { if (d.id.equals(deviceId)) return d.measures; }
        return new ArrayList<>();
    }

    /**
     * Récupère tous les péripériques
     * @return tous les péripériques du registre
     */
    public List<Device> getAllDevices() {
        return devices;
    }

    /**
     * Récupère tous les identifiants des péripériques
     * @return tous les identifiants
     */
    public List<String> getDeviceIds() {
        List<String> deviceIds = new ArrayList<>();
        devices.forEach(d -> deviceIds.add(d.id));
        return deviceIds;
    }
}