package com.example.fernando.myapplication.Activities;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Pair;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.example.fernando.myapplication.Common.ServletPostAsyncTask;
import com.example.fernando.myapplication.Common.UserSessionManager;
import com.example.fernando.myapplication.R;

/**
 * Created by fernando on 07/04/15.
 */

public class LogInActivity extends ActionBarActivity implements View.OnClickListener {

    // To close this activity from SignUp Activity
    public static final String ACTION_CLOSE = "yourPackageName.ACTION_CLOSE";
    private FinishSignalReceiver firstReceiver;

    // To user enter password and username
    Button btnLogin;
    EditText txtUsername, txtPassword;
    // User Session Manager Class
    UserSessionManager session;
    SharedPreferences mSharedPreferences;
    private static final String PREFS = "prefs";
    private static final String PREF_NAME = "name";
    private static final String PREF_PASS= "password";

    private static final String url = "http://10.0.2.2:8080/hello";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Tell the login which XML layout is right
        setContentView(R.layout.login);

        Button button1 = (Button) findViewById(R.id.button1);
        button1.setOnClickListener(this);

        Button button2 = (Button) findViewById(R.id.button2);
        button2.setOnClickListener(this);

        IntentFilter filter = new IntentFilter(ACTION_CLOSE);
        firstReceiver = new FinishSignalReceiver();
        registerReceiver(firstReceiver, filter);


        // get Email, Password input text
        txtUsername = (EditText) findViewById(R.id.txtUsername);
        txtPassword = (EditText) findViewById(R.id.txtPassword);

//        Toast.makeText(getApplicationContext(),
//                "User Login Status: " + session.isUserLoggedIn(),
//                Toast.LENGTH_LONG).show();


        // User Login button
        btnLogin = (Button) findViewById(R.id.button1);
        btnLogin.setOnClickListener(this);

        mSharedPreferences = getSharedPreferences(PREFS, MODE_PRIVATE);
        // Enable the "Up" button for more navigation options
//        getActionBar().setDisplayHomeAsUpEnabled(true);
    }

    @Override
    public void onClick(View v) {

        if (v.getId() == R.id.button1) {

            // Get username, password from EditText
            String username = txtUsername.getText().toString();
            String password = txtPassword.getText().toString();

            // Validate if username, password is filled
            if(username.trim().length() > 0 && password.trim().length() > 0) {

                SharedPreferences.Editor e = mSharedPreferences.edit();
                e.putString(PREF_NAME, username);
                e.putString(PREF_PASS, password);
                e.commit();

//                String packageToServer = doPackage();

                new ServletPostAsyncTask().execute(new Pair<Context, String>(this, "packageToServer"),
                        new Pair<Context, String>(this, "http://10.0.2.2:8080/hello"),
                        new Pair<Context, String>(this, "post"));


                // create an Intent to take you over to a new DetailActivity
                Intent chatsHall = new Intent(this, ChatsHallActivity.class);

                // pack away the data about the cover
                // into your Intent before you head out
                chatsHall.putExtra("coverID", "undato");

                // TODO: add any other data you'd like as Extras

                // start the next Activity using your prepared Intent
                startActivity(chatsHall);
                finish();

            } else {

                // user didn't entered username or password
                Toast.makeText(getApplicationContext(), "Please enter username and password", Toast.LENGTH_LONG).show();

            }

        } else if (v.getId() == R.id.button2) {

            // create an Intent to take you over to a new DetailActivity
            Intent signUpActivity = new Intent(this, SignUpActivity.class);

            // pack away the data about the cover
            // into your Intent before you head out
            signUpActivity.putExtra("coverID", "undato");

            // TODO: add any other data you'd like as Extras

            // start the next Activity using your prepared Intent
            startActivity(signUpActivity);
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unregisterReceiver(firstReceiver);
    }

    class FinishSignalReceiver extends BroadcastReceiver {
        @Override
        public void onReceive(Context context, Intent intent) {
//            Log.e("FirstReceiver", "FirstReceiver");
            if (intent.getAction().equals(ACTION_CLOSE)) {
                LogInActivity.this.finish();
            }
        }
    }

}
