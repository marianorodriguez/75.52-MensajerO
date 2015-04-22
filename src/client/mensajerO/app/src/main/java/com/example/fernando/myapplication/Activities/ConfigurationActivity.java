package com.example.fernando.myapplication.Activities;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.View;
import android.widget.Button;

import com.example.fernando.myapplication.R;

/**
 * Created by fernando on 10/04/15.
 */
public class ConfigurationActivity extends ActionBarActivity implements View.OnClickListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Tell the login which XML layout is right
        setContentView(R.layout.configuration);

        Button button1 = (Button) findViewById(R.id.button1);
        button1.setOnClickListener(this);

        Button button2 = (Button) findViewById(R.id.button2);
        button2.setOnClickListener(this);

        // Enable the "Up" button for more navigation options
//        getActionBar().setDisplayHomeAsUpEnabled(true);
    }

    @Override
    public void onClick(View v) {

        if (v.getId() == R.id.button1) {
            //Cancel button
            finish();
        } else if (v.getId() == R.id.button2 ) {
            //Done button

            //ARMAR EL PAQETE CORRESPONDIENTE CON FOTO DE USER
            // HACER EL POST
            // SI EL SERVER DA EL OK SALIR (TOCAR CONSTANTS), SINO TIRAR UN TOAST QE NO SE PUDO ENVIAR
            // Y QUEDARSE AHI.
        }
    }
}
