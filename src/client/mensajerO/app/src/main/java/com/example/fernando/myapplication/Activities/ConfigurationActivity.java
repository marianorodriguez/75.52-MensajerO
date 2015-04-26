package com.example.fernando.myapplication.Activities;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Pair;
import android.view.View;
import android.widget.Button;

import com.example.fernando.myapplication.Common.ServletPostAsyncTask;
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
            new ServletPostAsyncTask().execute(new Pair<Context, String>(this, "packageToServer"),
                    new Pair<Context, String>(this, "http://10.0.2.2:8080/config"),
                    new Pair<Context, String>(this, "post"));
            boolean ok = true;
            if (ok) {
//                TOCAR CONSTANTS
                finish();
            } else {
                // tirar toast de que no se pudo conectar con el server, verifique su conexion
            }

        }
    }
}
