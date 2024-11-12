package com.irc.proj_archi_iot.views;

import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.irc.proj_archi_iot.R;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link HistFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class HistFragment extends Fragment {

    public HistFragment() {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @return A new instance of fragment HistFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static HistFragment newInstance() {
        return new HistFragment();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_hist, container, false);
    }
}