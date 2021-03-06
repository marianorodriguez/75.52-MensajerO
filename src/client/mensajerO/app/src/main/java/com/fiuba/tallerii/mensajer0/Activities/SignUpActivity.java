package com.fiuba.tallerii.mensajer0.Activities;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Base64;
import android.util.Pair;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.fiuba.tallerii.mensajer0.Common.Constants;
import com.fiuba.tallerii.mensajer0.Common.MyLocationListener;
import com.fiuba.tallerii.mensajer0.Entities.User;
import com.fiuba.tallerii.mensajer0.R;
import com.fiuba.tallerii.mensajer0.Threads.SignUpPostAsyncTask;

import java.io.ByteArrayOutputStream;

/**
 * Esta clase representa la actividad para que el usuario pueda registrarse. 
 */

public class SignUpActivity extends ActionBarActivity implements View.OnClickListener {

    EditText txtUsername, txtPassword;
    SignUpPostAsyncTask signUpPost;
    SharedPreferences mSharedPref;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.signup);

        getSupportActionBar().hide();

        Button button2 = (Button) findViewById(R.id.signupbutton);
        button2.setOnClickListener(this);

        txtUsername = (EditText) findViewById(R.id.txtUsername);
        txtPassword = (EditText) findViewById(R.id.txtPassword);

        mSharedPref = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);
        Constants.ipServer = mSharedPref.getString("ipServer", "");

        signUpPost = new SignUpPostAsyncTask();
    }

    @Override
    public void onClick(View v) {

        if (v.getId() == R.id.signupbutton) {

            String username = txtUsername.getText().toString();
            String password = txtPassword.getText().toString();

            // Validate if username, password is filled
            if (username.trim().length() > 0 && password.trim().length() > 0) {

                password = LogInActivity.md5(password);
                User currentUser = new User(username, password);
                currentUser.location = getLocation();

                Constants.USER_KEEPED_LOCATION = currentUser.location;
                currentUser.status = "Online";

                Drawable myDrawable = getResources().getDrawable(R.drawable.defprofpic);
                currentUser.profile_picture = ((BitmapDrawable) myDrawable).getBitmap();

                String package_ = Constants.packager.wrap("signUp", currentUser);
                Constants.ipServer = mSharedPref.getString("ipServer", "");

                signUpPost.execute(new Pair<Context, String>(this, package_),
                        new Pair<Context, String>(this, Constants.signUpUrl),
                        new Pair<Context, String>(this, "post"));

                while (Constants.signUpOk.compareTo("") == 0) {
                    try {
                        Thread.sleep(10);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }

                if (Constants.signUpOk.contains("Error")) {
                    Toast.makeText(this, "Couldn't connect with server. " +
                            "Check your internet connection or try again later.", Toast.LENGTH_LONG).show();
                    txtUsername.setText("");
                    txtPassword.setText("");

                    Constants.signUpOk = "";
                    signUpPost = new SignUpPostAsyncTask();
                    return;
                } else {

                    if (Constants.signUpOk.compareTo("true") == 0) {

                        Constants.user = currentUser;

                        Constants.user.location = Constants.signUpLocation;

                        SharedPreferences.Editor e = mSharedPref.edit();
                        e.putString(Constants.PREF_NAME, username);
                        e.putString(Constants.PREF_PASS, password);
                        e.putString(username + "location", Constants.user.location);
                        e.putString(username + "picture", setDefaultPicture());
                        e.putString(username + "chats", "");
                        e.putString(username + "status", Constants.user.status);
                        e.commit();

                    } else {
                        Toast.makeText(this, "Username already exists, try another.", Toast.LENGTH_SHORT).show();
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

                    Intent myIntent = new Intent(LogInActivity.ACTION_CLOSE);
                    sendBroadcast(myIntent);

                    finish();
                }

            } else {
                Toast.makeText(getApplicationContext(),
                        "Please enter username and password.", Toast.LENGTH_SHORT).show();
            }

        } else {

            finish();
        }
    }
/**
*Retorna ubicación en coordenadas latitud;longitud
*/
    public String getLocation() {

        LocationManager mlocManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
        boolean net = mlocManager.isProviderEnabled(LocationManager.GPS_PROVIDER);
        Location l = null;
        if (net)
            l = mlocManager.getLastKnownLocation(LocationManager.GPS_PROVIDER);

        double l1 = 0;
        double l2 = 0;
        if (l != null) {
            l1 = l.getLongitude();
            l2 = l.getLatitude();
        }

        LocationListener mlocListener = new MyLocationListener(this);
        mlocManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 0, 0, mlocListener);
        return String.valueOf(l1) + ";" + String.valueOf(l2);
    }
/**
* Setea la imagen de perfil default. 
*/
    private String setDefaultPicture() {
        Drawable myDrawable = getResources().getDrawable(R.drawable.defprofpic);
        Bitmap defaultPicture = ((BitmapDrawable) myDrawable).getBitmap();

        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        defaultPicture.compress(Bitmap.CompressFormat.PNG, 100, baos);
        byte[] b = baos.toByteArray();
        String temp = Base64.encodeToString(b, Base64.DEFAULT);

        return temp;
    }
}
