package com.irc.proj_archi_iot.models;

import java.time.LocalDateTime;

public class Measure {

    public final MeasureType type;
    public final double value;

    public Measure(MeasureType type, double value) {
        this.type = type;
        this.value = value;
    }
}