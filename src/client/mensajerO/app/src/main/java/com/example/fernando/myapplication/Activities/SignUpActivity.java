package com.example.fernando.myapplication.Activities;

import android.app.ActionBar;
import android.app.Activity;
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
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Common.MyLocationListener;
import com.example.fernando.myapplication.Entities.User;
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
    SharedPreferences mSharedPref;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.signup);

        getSupportActionBar().hide();

        Button button1 = (Button) findViewById(R.id.backtologin);
        button1.setOnClickListener(this);

        Button button2 = (Button) findViewById(R.id.signupbutton);
        button2.setOnClickListener(this);

        // get Email, Password input text
        txtUsername = (EditText) findViewById(R.id.txtUsername);
        txtPassword = (EditText) findViewById(R.id.txtPassword);

        mSharedPref = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);
        Constants.ipServer = mSharedPref.getString("ipServer", "");

        signUpPost = new SignUpPostAsyncTask();
    }

    @Override
    public void onClick(View v) {

        if (v.getId() == R.id.signupbutton) {

//            Constants.ipServer = mSharedPref.getString("ipServer", "");

            String username = txtUsername.getText().toString();
            String password = txtPassword.getText().toString();

            // Validate if username, password is filled
            if(username.trim().length() > 0 && password.trim().length() > 0) {

                password = LogInActivity.md5(password);
                User currentUser = new User(username, password);
                currentUser.location = getLocation();
                currentUser.status = "online";

                Drawable myDrawable = getResources().getDrawable(R.drawable.ic_launcher);
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

                if (Constants.signUpOk.contains("Error")) {}

                if (Constants.signUpOk.compareTo("true") == 0) {

                    Constants.user = currentUser;

                    Constants.user.location = Constants.signUpLocation;

                    SharedPreferences.Editor e = mSharedPref.edit();
                    e.putString(Constants.PREF_NAME, username);
                    e.putString(Constants.PREF_PASS, password);
                    e.putString(username+"location", Constants.user.location);
                    e.putString(username+"picture", setDefaultPicture());
                    e.putString(username+"chats", "");
                    e.putString(username+"status", Constants.user.status);
                    e.commit();

                } else {
                    Toast.makeText(this, "Invalid username. Try another one.", Toast.LENGTH_SHORT).show();
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
                        "Please enter username and password", Toast.LENGTH_SHORT).show();
            }

        } else {

            finish();
        }
    }

    public String getLocation() {

        LocationManager mlocManager = (LocationManager)getSystemService(Context.LOCATION_SERVICE);
        boolean net = mlocManager.isProviderEnabled(LocationManager.GPS_PROVIDER);
        Location l = null;
        if(net)
            l= mlocManager.getLastKnownLocation(LocationManager.GPS_PROVIDER);

        double l1 = 0;
        double l2 = 0;
        if(l!=null)
        {
            l1 = l.getLongitude();
            l2 = l.getLatitude();
        }

        //Toast.makeText(getApplicationContext(),"location: " + l1 + "," + l2, Toast.LENGTH_LONG).show();
        LocationListener mlocListener = new MyLocationListener(this);
        mlocManager.requestLocationUpdates( LocationManager.GPS_PROVIDER, 0, 0, mlocListener);
        // VER SI l1 y l2 son distintas de cero --> si es asi mandar Unknown
        return String.valueOf(l1)+";"+String.valueOf(l2);
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
