package com.irc.proj_archi_iot.views;

import android.os.Bundle;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import androidx.fragment.app.Fragment;

import com.irc.proj_archi_iot.R;
import com.irc.proj_archi_iot.controllers.CommandHandler;
import com.irc.proj_archi_iot.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Binding de l'activité
    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        // Initialisation de l'UI
        initUI();
    }

    /**
     * Initialise l'UI et associe les éléments de navigation.
     */
    private void initUI() {
        initNavMenu();
    }

    /**
     * Initialise le menu de navigation.
     */
    private void initNavMenu() {
        replaceFragment(HomeFragment.newInstance());
        binding.bottomNavigationView.setOnItemSelectedListener(item -> {

            if (item.getItemId() == R.id.home) {
                replaceFragment(HomeFragment.newInstance());
            } else if (item.getItemId() == R.id.cmd) {
                replaceFragment(CmdFragment.newInstance());
            } else if (item.getItemId() == R.id.hist) {
                replaceFragment(HistFragment.newInstance());
            }

            return true;
        });
    }

    /**
     * Remplace le fragment actuel par le fragment spécifié.
     *
     * @param fragment
     */
    private void replaceFragment(Fragment fragment) {
        getSupportFragmentManager()
            .beginTransaction()
            .replace(R.id.frame_layout, fragment)
            .commit();
    }
}