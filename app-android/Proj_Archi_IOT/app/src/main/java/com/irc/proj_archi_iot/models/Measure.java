package com.irc.proj_archi_iot.models;

import java.time.LocalDateTime;

/**
 * Modèle pour représenter une mesure avec son type et sa valeur
 */
public class Measure {

    public final MeasureType type;
    public final double value;

    public Measure(MeasureType type, double value) {
        this.type = type;
        this.value = value;
    }
}