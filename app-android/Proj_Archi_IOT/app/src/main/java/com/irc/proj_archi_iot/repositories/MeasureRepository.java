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

public class MeasureRepository {

    private static final MeasureRepository instance = new MeasureRepository();
    private MeasureRepository() {}
    public static MeasureRepository getInstance() { return instance; }

    private final List<Device> devices = new ArrayList() {
    };

    public void addDevice(Device device) {
        devices.add(device);
    }

    public void addMeasureToDevice(String deviceId, ReceivedMeasurement measure) {
        for (int i = 0; i < devices.size(); i++) {
            if (devices.get(i).id.equals(deviceId)) {
                devices.get(i).measures.add(measure);
            }
        }
    }

    public ReceivedMeasurement getLatestMeasureForDevice(String deviceId) {
        List<ReceivedMeasurement> measures = getMeasuresForDevice(deviceId);
        if (measures.isEmpty()) return null;
        ReceivedMeasurement latestMeasure = measures.get(0);
        for (ReceivedMeasurement measure : measures) {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                if (Instant.parse(measure.datetime).isAfter(Instant.parse(latestMeasure.datetime))) {
                    latestMeasure = measure;
                }
            }
            else {
                Log.e("Repo", "SDK version not API ok blbl");
            }
        }
        return latestMeasure;
    }

    public List<ReceivedMeasurement> getMeasuresForDevice(String deviceId) {
        for (Device d : devices) { if (d.id.equals(deviceId)) return d.measures; }
        return new ArrayList<>();
    }

    public List<Device> getAllDevices() {
        return devices;
    }

    public List<String> getDeviceIds() {
        List<String> deviceIds = new ArrayList<>();
        devices.forEach(d -> deviceIds.add(d.id));
        return deviceIds;
    }
}