package com.irc.proj_archi_iot.utils;

import com.irc.proj_archi_iot.models.MeasureType;

public class MeasureTypeUtils {

    public static String getMeasureUnit(MeasureType type) {
        switch (type) {
            case temperature: return "°C";
            case luminosity: return "Lux";
            case pressure: return "hPa";
            case humidity: return "%";
            default: return "";
        }
    }

}
