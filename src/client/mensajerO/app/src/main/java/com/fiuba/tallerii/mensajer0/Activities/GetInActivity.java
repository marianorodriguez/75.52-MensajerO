package com.fiuba.tallerii.mensajer0.Activities;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.fiuba.tallerii.mensajer0.Common.Constants;
import com.fiuba.tallerii.mensajer0.R;

/**
* Esta clase representa la actividad inicial donde se ingresa el IP del servidor. 
*/
public class GetInActivity extends ActionBarActivity implements View.OnClickListener {

    EditText ipContainer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.getin);

        Button mainButton = (Button) findViewById(R.id.backtologin);
        mainButton.setOnClickListener(this);

        ipContainer = (EditText) findViewById(R.id.ipedittext);
        getSupportActionBar().hide();
    }

    @Override
    public void onClick(View v) {

        EditText ip = (EditText) findViewById(R.id.ipedittext);
        if (ip.getText().toString().isEmpty()) {
            Toast.makeText(this, "Enter server's ip!", Toast.LENGTH_SHORT).show();
            return;
        }

        SharedPreferences mSharedPref = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);
        SharedPreferences.Editor e = mSharedPref.edit();
        e.putString("ipServer", ipContainer.getText().toString());
        e.commit();
        Constants.setIp(ipContainer.getText().toString());

        Intent logIn = new Intent(this, LogInActivity.class);
        startActivity(logIn);
        overridePendingTransition(R.anim.open_next, R.anim.close_main);
        finish();
    }
}
