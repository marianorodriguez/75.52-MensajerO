package com.example.fernando.myapplication.Activities;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.example.fernando.myapplication.Common.UserSessionManager;
import com.example.fernando.myapplication.R;

/**
 * Created by fernando on 10/04/15.
 */
public class SignUpActivity extends ActionBarActivity implements View.OnClickListener {

    // To user enter password and username
    Button btnLogin;
    EditText txtUsername, txtPassword;
    // User Session Manager Class
    UserSessionManager session;
    SharedPreferences mSharedPreferences;
    private static final String PREFS = "prefs";
    private static final String PREF_NAME = "Fer";
    private static final String PREF_PASSW = "Fer";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Tell the login which XML layout is right
        setContentView(R.layout.signup);

        Button button1 = (Button) findViewById(R.id.button1);
        button1.setOnClickListener(this);

        Button button2 = (Button) findViewById(R.id.button2);
        button2.setOnClickListener(this);


        // get Email, Password input text
        txtUsername = (EditText) findViewById(R.id.txtUsername);
        txtPassword = (EditText) findViewById(R.id.txtPassword);

//        Toast.makeText(getApplicationContext(),
//                "User Login Status: " + session.isUserLoggedIn(),
//                Toast.LENGTH_LONG).show();

        // User Login button
        btnLogin = (Button) findViewById(R.id.button1);
        mSharedPreferences = getSharedPreferences(PREFS, MODE_PRIVATE);

        // Enable the "Up" button for more navigation options
//        getActionBar().setDisplayHomeAsUpEnabled(true);
    }

    @Override
    public void onClick(View v) {

        if (v.getId() == R.id.button2 ) {
            // Get username, password from EditText
            String username = txtUsername.getText().toString();
            String password = txtPassword.getText().toString();

            // Validate if username, password is filled
            if(username.trim().length() > 0 && password.trim().length() > 0) {

                SharedPreferences.Editor e = mSharedPreferences.edit();
                e.putString(PREF_NAME, username);
                e.putString(PREF_PASSW, password);
                e.commit();

                // Welcome the new user
//                Toast.makeText(getApplicationContext(), "Welcome, " + username + "!", Toast.LENGTH_LONG).show();

                // create an Intent to take you over to a new DetailActivity
                Intent chatsHall = new Intent(this, ChatsHallActivity.class);

                // pack away the data about the cover
                // into your Intent before you head out
                chatsHall.putExtra("coverID", "undato");

                // TODO: add any other data you'd like as Extras

                // start the next Activity using your prepared Intent
                startActivity(chatsHall);
                // create an Intent to take you over to a new DetailActivity
                Intent config = new Intent(this, ConfigurationActivity.class);

                // pack away the data about the cover
                // into your Intent before you head out
                config.putExtra("coverID", "undato");

                // TODO: add any other data you'd like as Extras

                // start the next Activity using your prepared Intent
                startActivity(config);


                // y hacer finish de log IN tambien !!!!!!!!!!!!!
                Intent myIntent = new Intent(LogInActivity.ACTION_CLOSE);
                sendBroadcast(myIntent);

                finish();

            } else {

                // user didn't entered username or password
                Toast.makeText(getApplicationContext(), "Please enter username and password", Toast.LENGTH_LONG).show();

            }

        } else {
//            Intent login = new Intent(this, LogInActivity.class);
//
//            // pack away the data about the cover
//            // into your Intent before you head out
//            login.putExtra("coverID", "undato");
//
//            // TODO: add any other data you'd like as Extras
//
//            // start the next Activity using your prepared Intent
//            startActivity(login);
            finish();
        }
    }
}
