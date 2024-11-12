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

    private EditText fieldDeviceId;
    private Spinner spnTemperature, spnLuminosity, spnPressure, spnHumidity;
    private TextView textTemperature, textLuminosity, textPressure, textHumidity;
    private Button btnSetOrder, btnGetMeasurements;

    private LinearLayout spnContainer;
    private Spinner deviceIdsSpinner;

    public CmdFragment() {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @return A new instance of fragment CmdFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static CmdFragment newInstance() {
        return new CmdFragment();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_cmd, container, false);

        spnContainer = view.findViewById(R.id.spinner_container);
        deviceIdsSpinner = view.findViewById(R.id.spn_device_id);

        populateDeviceIdSpinner(view);

        for (int i = 0; i < 4; i++) {
            addMeasurementSpinner(i);
        }

        Button btn = view.findViewById(R.id.btn_send_order);
        btn.setOnClickListener(v -> {
            String selectedDeviceId = deviceIdsSpinner.getSelectedItem().toString();
            String code = retrieveSpinnerValues();

            CommandHandler.getInstance().setOrder(selectedDeviceId, code);
        });

        return view;
    }

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
        View spinner = LayoutInflater.from(getContext()).inflate(R.layout.position_spinner, spnContainer, false);

        ((TextView)spinner.findViewById(R.id.tv_index)).setText(String.valueOf(i+1));
        ((Spinner)spinner.findViewById(R.id.spn_measure)).setSelection(i);
        ((Spinner)spinner.findViewById(R.id.spn_measure)).setId(i);

        spnContainer.addView(spinner);
    }

    private String retrieveSpinnerValues() {
        int count = spnContainer.getChildCount();
        Character[] code = new Character[4];
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