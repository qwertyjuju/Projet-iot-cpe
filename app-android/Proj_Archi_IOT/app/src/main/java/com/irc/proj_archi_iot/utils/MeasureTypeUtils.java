package com.irc.proj_archi_iot.utils;

import com.irc.proj_archi_iot.models.MeasureType;

/**
 * Classe utilitaire pour les types de mesures.
 */
public class MeasureTypeUtils {

    /**
     * Retourne l'unité de mesure correspondante au type de mesure.
     * @param type Type de mesure
     * @return Unité de mesure
     */
    public static String getMeasureUnit(MeasureType type) {
        switch (type) {
            case temp: return "°C";
            case lux: return "Lux";
            case pres: return "hPa";
            case hum: return "%";
            case ir: return "%";
            case uv: return "%";
            default: return "";
        }
    }

}
