package com.example.fernando.myapplication.Activities;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Pair;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Common.ServletPostAsyncTask;
import com.example.fernando.myapplication.Common.User;
import com.example.fernando.myapplication.R;

/**
 * Created by fernando on 10/04/15.
 */

public class SignUpActivity extends ActionBarActivity implements View.OnClickListener {

    // To user enter password and username
    EditText txtUsername, txtPassword;
    ServletPostAsyncTask signUpPost;
    String ok;

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

        Constants.mSharedPreferences = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);

        signUpPost = new ServletPostAsyncTask();
        ok = "";
    }

    @Override
    public void onClick(View v) {

        if (v.getId() == R.id.button2 ) {

            String username = txtUsername.getText().toString();
            String password = txtPassword.getText().toString();

            // Validate if username, password is filled
            if(username.trim().length() > 0 && password.trim().length() > 0) {

                password = LogInActivity.md5(password);
                User currentUser = new User(username, password);

                String package_ = Constants.packager.doPackage("logIn", currentUser);

                signUpPost.execute(new Pair<Context, String>(this, package_),
                        new Pair<Context, String>(this,Constants.signUpUrl),
                        new Pair<Context, String>(this, "post"));

                while (ok.compareTo("") == 0) {}

                if (ok.contains("Error")) {}

                if (ok.compareTo("true") == 0) {
                    Constants.user = currentUser;

                    SharedPreferences.Editor e = Constants.mSharedPreferences.edit();
                    e.putString(Constants.PREF_NAME, username);
                    e.putString(Constants.PREF_PASS, password);
                    e.commit();

                } else {
                    Toast.makeText(this, "Nombre de usuario invalido. Ingrese nuevamente.", Toast.LENGTH_LONG).show();
                    currentUser = null;
                    txtUsername.setText("");
                    txtPassword.setText("");
                    return;
                }

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
