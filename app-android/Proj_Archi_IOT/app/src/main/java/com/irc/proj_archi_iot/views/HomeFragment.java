package com.irc.proj_archi_iot.views;

import static com.irc.proj_archi_iot.utils.MeasureTypeUtils.getMeasureUnit;

import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.Spinner;
import android.widget.TextView;

import com.irc.proj_archi_iot.R;
import com.irc.proj_archi_iot.controllers.CommandHandler;
import com.irc.proj_archi_iot.models.ReceivedMeasurement;
import com.irc.proj_archi_iot.repositories.MeasureRepository;

import java.util.List;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link HomeFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class HomeFragment extends Fragment {

    private LinearLayout cardContainer;

    private Spinner deviceIdsSpinner;

    public HomeFragment() {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @return A new instance of fragment HomeFragment.
     */
    public static HomeFragment newInstance() {
        return new HomeFragment();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_home, container, false);

        deviceIdsSpinner = view.findViewById(R.id.spn_device_id);
        cardContainer = view.findViewById(R.id.card_container);

        populateDeviceIdSpinner();

        view.findViewById(R.id.btn_get_measure).setOnClickListener(v -> {
            cardContainer.removeAllViews();

            String selectedDeviceId = deviceIdsSpinner.getSelectedItem().toString();
            CommandHandler.getInstance().getMeasure(selectedDeviceId);
            ReceivedMeasurement measure = MeasureRepository.getInstance().getLatestMeasureForDevice(selectedDeviceId);

            if (measure == null) return;

            addMeasurementCard(measure.temperature.type.name(), String.valueOf(measure.temperature.value), getMeasureUnit(measure.temperature.type), R.drawable.ic_temperature);
            addMeasurementCard(measure.luminosity.type.name(), String.valueOf(measure.luminosity.value), getMeasureUnit(measure.luminosity.type), R.drawable.ic_luminosity);
            addMeasurementCard(measure.pressure.type.name(), String.valueOf(measure.pressure.value), getMeasureUnit(measure.pressure.type), R.drawable.ic_pressure);
            addMeasurementCard(measure.humidity.type.name(), String.valueOf(measure.humidity.value), getMeasureUnit(measure.humidity.type), R.drawable.ic_humidity);
        });

        return view;
    }

    private void populateDeviceIdSpinner() {
        List<String> deviceIds = MeasureRepository.getInstance().getDeviceIds();
        for (String deviceId : deviceIds) CommandHandler.getInstance().getMeasures(deviceId);
        ArrayAdapter adapter = new ArrayAdapter(
                getContext(),
                android.R.layout.simple_spinner_dropdown_item,
                deviceIds
        );

        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        deviceIdsSpinner.setAdapter(adapter);
    }

    private void addMeasurementCard(String name, String value, String unit, int iconResId) {
        View card = LayoutInflater.from(getContext()).inflate(R.layout.measurement_card, cardContainer, false);

        ((TextView)card.findViewById(R.id.measurement_name)).setText(name);
        ((TextView)card.findViewById(R.id.measurement_value)).setText(value);
        ((TextView)card.findViewById(R.id.measurement_unit)).setText(unit);
        ((ImageView)card.findViewById(R.id.measurement_icon)).setImageResource(iconResId);

        cardContainer.addView(card);
    }
}