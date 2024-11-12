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

public class JsonUtils {

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

    public static ReceivedMeasurement deserializeMeasurement(JSONObject jsonObject) {
        try {
            double[] values = new double[4];
            values[0] = jsonObject.getDouble("temperature");
            values[1] = jsonObject.getDouble("luminosity");
            values[2] = jsonObject.getDouble("pressure");
            values[3] = jsonObject.getDouble("humidity");
            String datetime = jsonObject.getString("datetime");

            return new ReceivedMeasurement(values, datetime);

        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }
}
