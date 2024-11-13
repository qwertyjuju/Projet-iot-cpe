package com.irc.proj_archi_iot.views;

import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.Spinner;
import android.widget.TextView;

import com.irc.proj_archi_iot.R;
import com.irc.proj_archi_iot.controllers.CommandHandler;
import com.irc.proj_archi_iot.repositories.MeasureRepository;

import java.util.List;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link CmdFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class CmdFragment extends Fragment {

    private LinearLayout spnContainer;
    private Spinner deviceIdsSpinner;

    public CmdFragment() {
        // Required empty public constructor
    }

    public static CmdFragment newInstance() {
        return new CmdFragment();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        // Inflation du layout du fragment
        View view = inflater.inflate(R.layout.fragment_cmd, container, false);

        // Initialisation des éléments de l'UI
        spnContainer = view.findViewById(R.id.spinner_container);
        deviceIdsSpinner = view.findViewById(R.id.spn_device_id);

        // Remplissage du spinner avec les ID des appareils
        populateDeviceIdSpinner(view);

        // Ajout des spinners de sélection d'ordre des mesures
        for (int i = 0; i < 4; i++) {
            addMeasurementSpinner(i);
        }

        // Gestionnaire d'événement pour le bouton d'envoi de l'ordre
        view.findViewById(R.id.btn_send_order).setOnClickListener(v -> {
            // Récupération de l'ID de l'appareil sélectionnée
            String selectedDeviceId = deviceIdsSpinner.getSelectedItem().toString();

            // Récupération des valeurs des spinners
            String code = retrieveSpinnerValues();

            // Envoi de l'ordre au serveur
            CommandHandler.getInstance().setOrder(selectedDeviceId, code);
        });

        return view;
    }

    /**
     * Remplit le spinner avec les ID des appareils disponibles.
     *
     * @param view Vue du fragment
     */
    private void populateDeviceIdSpinner(View view) {
        List<String> deviceIds = MeasureRepository.getInstance().getDeviceIds();
        for (String deviceId : deviceIds) CommandHandler.getInstance().getMeasures(deviceId);
        ArrayAdapter adapter = new ArrayAdapter(
                getContext(),
                android.R.layout.simple_spinner_dropdown_item,
                deviceIds
        );

        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        ((Spinner)view.findViewById(R.id.spn_device_id)).setAdapter(adapter);
    }

    private void addMeasurementSpinner(int i) {
        // Création de la vue du spinner
        View spinner = LayoutInflater.from(getContext()).inflate(R.layout.position_spinner, spnContainer, false);

        // Attribution des valeurs aux éléments du spinner
        ((TextView)spinner.findViewById(R.id.tv_index)).setText(String.valueOf(i+1));
        ((Spinner)spinner.findViewById(R.id.spn_measure)).setSelection(i);
        spinner.findViewById(R.id.spn_measure).setId(i);

        // Ajout du spinner au conteneur
        spnContainer.addView(spinner);
    }

    /**
     * Récupère les valeurs sélectionnées dans les spinners et les concatène en une chaîne de caractères.
     *
     * @return Chaîne de caractères contenant l'ordre d'affichage des mesures.
     */
    private String retrieveSpinnerValues() {
        int count = spnContainer.getChildCount();
        Character[] code = new Character[4];

        // Pour chaque spinner, récupération de la valeur sélectionnée et ajout de l'initiale de la mesure à la chaîne de caractères.
        for (int i = 0; i < count; i++) {
            View spinnerView = spnContainer.getChildAt(i);
            Spinner spinner = spinnerView.findViewById(i);

            if (spinner != null) {
                code[i] = spinner.getSelectedItem().toString().charAt(0);
            }
        }

        StringBuilder sb = new StringBuilder();
        for (Character ch : code) {
            sb.append(ch);
        }
        return sb.toString();
    }
}