package com.example.fernando.myapplication.Activities;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Base64;
import android.util.Pair;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Common.User;
import com.example.fernando.myapplication.R;
import com.example.fernando.myapplication.Threads.SignUpPostAsyncTask;

import java.io.ByteArrayOutputStream;

/**
 * Created by fernando on 10/04/15.
 */

public class SignUpActivity extends ActionBarActivity implements View.OnClickListener {

    // To user enter password and username
    EditText txtUsername, txtPassword;
    SignUpPostAsyncTask signUpPost;
    SharedPreferences mSharedPreferences;

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

        mSharedPreferences = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);

        signUpPost = new SignUpPostAsyncTask();
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

                String package_ = Constants.packager.wrap("signUp", currentUser);

                signUpPost.execute(new Pair<Context, String>(this, package_),
                        new Pair<Context, String>(this,Constants.signUpUrl),
                        new Pair<Context, String>(this, "post"));

                while (Constants.signUpOk.compareTo("") == 0) {
                    try {
                        Thread.sleep(10);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }

                if (Constants.signUpOk.contains("Error")) {}

                if (Constants.signUpOk.compareTo("true") == 0) {
                    Constants.user = currentUser;
                    Constants.user.location = "Unknown";
                    Constants.user.status = "online";

                    // ACA SETEAR LA IMAGEN DEFAULT y EL ESTADO DEFAULT
                    Drawable myDrawable = getResources().getDrawable(R.drawable.ic_launcher);
                    Constants.user.profilePicture = ((BitmapDrawable) myDrawable).getBitmap();

                    SharedPreferences.Editor e = mSharedPreferences.edit();
                    e.putString(Constants.PREF_NAME, username);
                    e.putString(Constants.PREF_PASS, password);
                    e.putString(username+"location", "Unknown");
                    e.putString(username+"picture", setDefaultPicture());
                    e.putString(username+"chats", "");
                    e.putString(username+"status", "online");
                    e.commit();

                } else {
                    Toast.makeText(this, "Invalid username. Try another one.", Toast.LENGTH_LONG).show();
                    currentUser = null;
                    txtUsername.setText("");
                    txtPassword.setText("");

                    Constants.signUpOk = "";
                    signUpPost = new SignUpPostAsyncTask();
                    return;
                }

                Intent chatsHall = new Intent(this, ChatsHallActivity.class);
                startActivity(chatsHall);

                Intent config = new Intent(this, ConfigurationActivity.class);
                startActivity(config);

                // hago finish de log in tambien
                Intent myIntent = new Intent(LogInActivity.ACTION_CLOSE);
                sendBroadcast(myIntent);

                finish();

            } else {
                // user didn't entered username or password
                Toast.makeText(getApplicationContext(),
                        "Please enter username and password", Toast.LENGTH_LONG).show();
            }

        } else {

            finish();
        }
    }

    private String setDefaultPicture() {
        Drawable myDrawable = getResources().getDrawable(R.drawable.ic_launcher);
        Bitmap defaultPicture = ((BitmapDrawable) myDrawable).getBitmap();

        ByteArrayOutputStream baos = new  ByteArrayOutputStream();
        defaultPicture.compress(Bitmap.CompressFormat.PNG, 100, baos);
        byte [] b=baos.toByteArray();
        String temp= Base64.encodeToString(b, Base64.DEFAULT);

        return temp;
    }
}
