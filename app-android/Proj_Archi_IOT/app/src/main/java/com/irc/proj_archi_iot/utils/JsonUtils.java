package com.irc.proj_archi_iot.utils;

import android.os.Build;
import android.util.Log;

import androidx.annotation.RequiresApi;

import com.irc.proj_archi_iot.models.ReceivedMeasurement;
import com.irc.proj_archi_iot.repositories.MeasureRepository;

import org.json.JSONException;
import org.json.JSONObject;

import java.lang.reflect.Field;
import java.time.LocalDateTime;

/**
 * Classe utilitaire pour la sérialisation et la désérialisation de JSON.
 */
public class JsonUtils {

    /**
     * Serialise un objet en JSON.
     * @param obj Objet à sérialiser
     * @return Objet JSON
     * @throws JSONException En cas d'erreur de sérialisation
     */
    public static JSONObject serialize(Object obj) throws JSONException {
        JSONObject jsonObject = new JSONObject();

        Field[] fields = obj.getClass().getDeclaredFields();

        for (Field field : fields) {
            field.setAccessible(true);
            try {
                jsonObject.put(field.getName(), field.get(obj));
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            }
        }

        return jsonObject;
    }

    /**
     * Désérialise un objet JSON en un objet Java.
     * @param jsonObject Objet JSON à désérialiser
     * @param timestamp Timestamp de la mesure
     * @return Objet Java
     */
    public static ReceivedMeasurement deserializeMeasurement(JSONObject jsonObject, String timestamp) {
        try {
            double[] values = new double[6];
            values[0] = jsonObject.optDouble("temp", Double.NaN);
            values[1] = jsonObject.optDouble("lux", Double.NaN);
            values[2] = jsonObject.optDouble("pres", Double.NaN);
            values[3] = jsonObject.optDouble("hum", Double.NaN);
            values[4] = jsonObject.optDouble("ir", Double.NaN);
            values[5] = jsonObject.optDouble("uv", Double.NaN);

            return new ReceivedMeasurement(values, timestamp);

        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }
}
