package com.irc.proj_archi_iot.views;

import static com.irc.proj_archi_iot.utils.MeasureTypeUtils.getMeasureUnit;

import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
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

        // Inflation du layout du fragment
        View view = inflater.inflate(R.layout.fragment_home, container, false);

        // Initialisation des éléments de l'UI
        deviceIdsSpinner = view.findViewById(R.id.spn_device_id);
        cardContainer = view.findViewById(R.id.card_container);

        // Remplissage du spinner avec les ID des appareils
        populateDeviceIdSpinner();

        // Gestionnaire d'événement pour le bouton de récupération de la mesure
        view.findViewById(R.id.btn_get_measure).setOnClickListener(v -> {
            // Nettoyage du conteneur de cartes
            cardContainer.removeAllViews();

            // Récupération de l'ID de l'appareil sélectionné
            String selectedDeviceId = deviceIdsSpinner.getSelectedItem().toString();

            // Récupération de la dernière mesure pour l'appareil depuis le serveur
            CommandHandler.getInstance().getMeasure(selectedDeviceId);

            ReceivedMeasurement measure = null;
            do {
                // Attente jusqu'à la réception d'une mesure
                try {
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            while ((measure = MeasureRepository.getInstance().getLatestMeasureForDevice(selectedDeviceId)) == null);

            // Ajout des cartes de mesure au conteneur
            addMeasurementCard(measure.temp.type.name(), String.valueOf(measure.temp.value), getMeasureUnit(measure.temp.type), R.drawable.ic_temperature);
            addMeasurementCard(measure.lux.type.name(), String.valueOf(measure.lux.value), getMeasureUnit(measure.lux.type), R.drawable.ic_luminosity);
            addMeasurementCard(measure.pres.type.name(), String.valueOf(measure.pres.value), getMeasureUnit(measure.pres.type), R.drawable.ic_pressure);
            addMeasurementCard(measure.hum.type.name(), String.valueOf(measure.hum.value), getMeasureUnit(measure.hum.type), R.drawable.ic_humidity);
            addMeasurementCard(measure.ir.type.name(), String.valueOf(measure.ir.value), getMeasureUnit(measure.ir.type), R.drawable.ic_ir);
            addMeasurementCard(measure.uv.type.name(), String.valueOf(measure.uv.value), getMeasureUnit(measure.uv.type), R.drawable.ic_uv);
        });

        // Retour de la vue
        return view;
    }

    /**
     * Remplit le spinner avec les ID des appareils disponibles.
     */
    private void populateDeviceIdSpinner() {
        List<String> deviceIds = MeasureRepository.getInstance().getDeviceIds();
        for (String deviceId : deviceIds) CommandHandler.getInstance().getMeasures(deviceId);

        // Création de l'adapter pour le spinner
        ArrayAdapter adapter = new ArrayAdapter(
                getContext(),
                android.R.layout.simple_spinner_dropdown_item,
                deviceIds
        );

        // Configuration du style du spinner
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        // Attribution de l'adapter au spinner
        deviceIdsSpinner.setAdapter(adapter);
    }

    /**
     * Ajoute une carte de mesure au conteneur.
     * @param name Nom de la mesure
     * @param value Valeur de la mesure
     * @param unit Unité de la mesure
     * @param iconResId ID du drawable de l'icône de la mesure
     */
    private void addMeasurementCard(String name, String value, String unit, int iconResId) {

        // Création de la vue de la carte
        View card = LayoutInflater.from(getContext()).inflate(R.layout.measurement_card, cardContainer, false);

        // Attribution des valeurs aux éléments de la carte
        ((TextView)card.findViewById(R.id.measurement_name)).setText(name);
        ((TextView)card.findViewById(R.id.measurement_value)).setText(value);
        ((TextView)card.findViewById(R.id.measurement_unit)).setText(unit);
        ((ImageView)card.findViewById(R.id.measurement_icon)).setImageResource(iconResId);

        // Ajout de la carte au conteneur
        cardContainer.addView(card);
    }
}