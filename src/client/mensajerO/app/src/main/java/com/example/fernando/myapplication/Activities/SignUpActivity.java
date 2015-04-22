package com.example.fernando.myapplication.Activities;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.R;

/**
 * Created by fernando on 10/04/15.
 */

public class SignUpActivity extends ActionBarActivity implements View.OnClickListener {

    // To user enter password and username
    EditText txtUsername, txtPassword;
    // User Session Manager Class
//    UserSessionManager session;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
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
//        btnLogin = (Button) findViewById(R.id.button1);
        Constants.mSharedPreferences = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);

    }

    @Override
    public void onClick(View v) {

        if (v.getId() == R.id.button2 ) {
            // Get username, password from EditText
            String username = txtUsername.getText().toString();
            String password = txtPassword.getText().toString();

            // Validate if username, password is filled
            if(username.trim().length() > 0 && password.trim().length() > 0) {

                SharedPreferences.Editor e = Constants.mSharedPreferences.edit();
                e.putString(Constants.PREF_NAME, username);
                e.putString(Constants.PREF_PASS, password);
                e.commit();

                // CREAR UN USER
                // hacer el package
                // hacer el post
                // tomar el response
                // si todo ok (Constants.user = newUser;) seguir,
                // sino tirar un toast, borrar el user, y borrar los edit text (o
                // ejecutar nuevamente la activity con algun flag para qe tire el toast
                // de user y password incorrecta)

                Intent chatsHall = new Intent(this, ChatsHallActivity.class);
                startActivity(chatsHall);

                Intent config = new Intent(this, ConfigurationActivity.class);
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

            finish();
        }
    }
}
