package com.irc.proj_archi_iot.models;

import java.util.ArrayList;
import java.util.List;

/**
 * Modèle pour représenter un périphérique IoT
 */
public class Device {
    public final String id;
    public final String name;
    public List<ReceivedMeasurement> measures;

    public Device(String id, String name) {
        this.id = id;
        this.name = name;
        this.measures = new ArrayList<>();
    }
}