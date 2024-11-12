package com.irc.proj_archi_iot.models;

import java.time.LocalDateTime;

public class ReceivedMeasurement {

    public final Measure temperature;
    public final Measure luminosity;
    public final Measure pressure;
    public final Measure humidity;

    public final String datetime;

    public ReceivedMeasurement(double[] values, String datetime) {
        temperature = new Measure(MeasureType.temperature, values[0]);
        luminosity = new Measure(MeasureType.luminosity, values[1]);
        pressure = new Measure(MeasureType.pressure, values[2]);
        humidity = new Measure(MeasureType.humidity, values[3]);

        this.datetime = datetime;
    }

}
