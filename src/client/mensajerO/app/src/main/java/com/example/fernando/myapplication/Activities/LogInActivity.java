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

import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Common.ServletPostAsyncTask;
import com.example.fernando.myapplication.Common.User;
import com.example.fernando.myapplication.Common.UserSessionManager;
import com.example.fernando.myapplication.R;

import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

/**
 * Created by fernando on 07/04/15.
 */

public class LogInActivity extends ActionBarActivity implements View.OnClickListener {

    // To close this activity from SignUp Activity
    public static final String ACTION_CLOSE = "yourPackageName.ACTION_CLOSE";
    private FinishSignalReceiver firstReceiver;

    EditText txtUsername, txtPassword;

    ServletPostAsyncTask logInPost;
    ServletPostAsyncTask currentChatsPost;
    public String ok;
    public String chats;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.login);

        Button button1 = (Button) findViewById(R.id.button1);
        button1.setOnClickListener(this);

        Button button2 = (Button) findViewById(R.id.button2);
        button2.setOnClickListener(this);

        IntentFilter filter = new IntentFilter(ACTION_CLOSE);
        firstReceiver = new FinishSignalReceiver();
        registerReceiver(firstReceiver, filter);

        // get Username, Password input text
        txtUsername = (EditText) findViewById(R.id.txtUsername);
        txtPassword = (EditText) findViewById(R.id.txtPassword);

        Constants.mSharedPreferences = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);

        logInPost = new ServletPostAsyncTask();
        currentChatsPost = new ServletPostAsyncTask();
        ok = "";
        chats = "";

    }

    public static String md5(String string) {
        byte[] hash = new byte[0];

        try {
            hash = MessageDigest.getInstance("MD5").digest(string.getBytes("UTF-8"));
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("Huh, MD5 should be supported?", e);
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }

        StringBuilder hex = new StringBuilder(hash.length * 2);

        for (byte b : hash) {
            int i = (b & 0xFF);
            if (i < 0x10) hex.append('0');
            hex.append(Integer.toHexString(i));
        }

        return hex.toString();
    }

    @Override
    public void onClick(View v) {

        if (v.getId() == R.id.button1) {

            // Get username, password from EditText
            String username = txtUsername.getText().toString();
            String password = txtPassword.getText().toString();

            // Validate if username, password is filled
            if(username.trim().length() > 0 && password.trim().length() > 0) {

                password = md5(password);
                User currentUser = new User(username, password);

                String package_ = Constants.packager.doPackage("logIn", currentUser);

                System.out.println(package_);

                logInPost.execute(new Pair<Context, String>(this, package_),
                        new Pair<Context, String>(this, Constants.logInUrl),
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
                    Toast.makeText(this, "Nombre de usuario o conyrasenia invalido. Ingrese nuevamente.", Toast.LENGTH_LONG).show();
                    currentUser = null;
                    txtUsername.setText("");
                    txtPassword.setText("");
                    return;
                }

                // posteo el mismo package_ de arriba
                currentChatsPost.execute(new Pair<Context, String>(this, package_),
                    new Pair<Context, String>(this, Constants.currentChatsUrl),
                    new Pair<Context, String>(this, "post"));

                while (chats.compareTo("") == 0) {}

                // user.chats = desempaquetar chats

                Intent chatsHall = new Intent(this, ChatsHallActivity.class);
                startActivity(chatsHall);
                finish();

            } else {

                // user didn't entered username or password
                Toast.makeText(getApplicationContext(), "Please enter username and password", Toast.LENGTH_LONG).show();

            }

        } else if (v.getId() == R.id.button2) {

            // create an Intent to take you over to a new DetailActivity
            Intent signUpActivity = new Intent(this, SignUpActivity.class);
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
