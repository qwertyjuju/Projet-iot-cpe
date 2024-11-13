package com.irc.proj_archi_iot.models;

/**
 * Modèle pour les mesures reçues du serveur
 */
public class ReceivedMeasurement {

    public final Measure temp;
    public final Measure lux;
    public final Measure pres;
    public final Measure hum;
    public final Measure ir;
    public final Measure uv;

    public final String datetime;

    public ReceivedMeasurement(double[] values, String datetime) {
        temp = new Measure(MeasureType.temp, values[0]);
        lux = new Measure(MeasureType.lux, values[1]);
        pres = new Measure(MeasureType.pres, values[2]);
        hum = new Measure(MeasureType.hum, values[3]);
        ir = new Measure(MeasureType.ir, values[4]);
        uv = new Measure(MeasureType.uv, values[5]);

        this.datetime = datetime;
    }

}
