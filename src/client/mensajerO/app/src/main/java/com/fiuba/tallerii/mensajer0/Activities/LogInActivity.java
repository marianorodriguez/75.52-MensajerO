package com.fiuba.tallerii.mensajer0.Activities;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
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
import android.widget.TextView;
import android.widget.Toast;

import com.fiuba.tallerii.mensajer0.Common.Constants;
import com.fiuba.tallerii.mensajer0.Common.MyLocationListener;
import com.fiuba.tallerii.mensajer0.Threads.LogInPostAsyncTask;
import com.fiuba.tallerii.mensajer0.Entities.User;
import com.example.fernando.mensajerO.R;

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

    LogInPostAsyncTask logInPost;

    //    CurrentChatsPostAsyncTask currentChatsGet;
    static SharedPreferences mSharedPref;

    public static SharedPreferences getmSharedPref() {
        return mSharedPref;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.login);

        getSupportActionBar().hide();

        Button button1 = (Button) findViewById(R.id.backtologin);
        button1.setOnClickListener(this);

        TextView button2 = (TextView) findViewById(R.id.signupbutton);
        button2.setOnClickListener(this);

        IntentFilter filter = new IntentFilter(ACTION_CLOSE);
        firstReceiver = new FinishSignalReceiver();
        registerReceiver(firstReceiver, filter);

        // get Username, Password input text
        txtUsername = (EditText) findViewById(R.id.txtUsername);
        txtPassword = (EditText) findViewById(R.id.txtPassword);

        logInPost = new LogInPostAsyncTask();
//        currentChatsGet = new CurrentChatsPostAsyncTask();

        mSharedPref = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);
        Constants.ipServer = mSharedPref.getString("ipServer", "");
        if (Constants.server != null)
            Constants.server.setSharedPref(mSharedPref);
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

        if (v.getId() == R.id.backtologin) {

            // Get username, password from EditText
            String username = txtUsername.getText().toString();
            String password = txtPassword.getText().toString();

            // Validate if username, password is filled
            if(username.trim().length() > 0 && password.trim().length() > 0) {

                password = md5(password);
                User currentUser = new User(username, password);

                String gps = mSharedPref.getString(username+"GPS", "");
                if (gps.isEmpty()) {
                    Toast.makeText(this, "Invalid username and/or password. Enter data again or sign up in MensajerO.", Toast.LENGTH_SHORT).show();
                    txtPassword.setText("");
                    txtUsername.setText("");

                    Constants.logInOk = "";
                    logInPost = new LogInPostAsyncTask();
                    return;
                }

                if (gps.compareTo("true") == 0)
                    Constants.GPS_ON = true;
                else
                    Constants.GPS_ON = false;

                if (Constants.GPS_ON) {
                    currentUser.location = getLocation();
                    Constants.USER_KEEPED_LOCATION = currentUser.location;
                } else {
                    currentUser.location = "0;0";
                }

                String package_ = Constants.packager.wrap("logIn", currentUser);
                Constants.ipServer = mSharedPref.getString("ipServer", "");

                logInPost.execute(new Pair<Context, String>(this, package_),
                        new Pair<Context, String>(this, Constants.logInUrl),
                        new Pair<Context, String>(this, "post"));

                int timeOut = 0;
                while (Constants.logInOk.compareTo("") == 0) {
                    try {
                        Thread.sleep(1000);
                        timeOut++;
                        if (timeOut == 4)
                            Constants.logInOk = "Error";
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }

                if (Constants.logInOk.contains("Error")) {
                    Toast.makeText(this, "Couldn't connect with server. Check your internet connection or try again later. Thanks.", Toast.LENGTH_LONG).show();
                    txtPassword.setText("");
                    txtUsername.setText("");
                    Constants.logInOk = "";
                    logInPost = new LogInPostAsyncTask();

                } else {

                    if (Constants.logInOk.compareTo("true") == 0) {
                        Constants.user = currentUser;

                        Constants.user.location = Constants.logInLocation;

                        Constants.user.status = Constants.logInStatus;
                        Constants.user.profile_picture = stringToBitmap(Constants.logInPicture);

                        SharedPreferences.Editor e = mSharedPref.edit();
                        e.putString(Constants.PREF_NAME, username);
                        e.putString(Constants.PREF_PASS, password);
                        e.commit();

                    } else {

                        Toast.makeText(this, "Invalid username and/or password. Enter data again or sign up in MensajerO.", Toast.LENGTH_SHORT).show();
                        txtPassword.setText("");
                        txtUsername.setText("");

                        Constants.logInOk = "";
                        logInPost = new LogInPostAsyncTask();
                        return;
                    }

                    Constants.logInOk = "";

                    Intent chatsHall = new Intent(this, ChatsHallActivity.class);
                    startActivity(chatsHall);
                    finish();
                }

            } else {

                // user didn't entered username or password
                Toast.makeText(this,
                        "Please enter username and password.",
                        Toast.LENGTH_SHORT).show();
            }

        } else if (v.getId() == R.id.signupbutton) {

            // create an Intent to take you over to a new DetailActivity
            Intent signUpActivity = new Intent(this, SignUpActivity.class);
            startActivity(signUpActivity);
        }
    }

    public Bitmap stringToBitmap(String pictureString){
        try {
            byte [] encodeByte = Base64.decode(pictureString, Base64.DEFAULT);
            Bitmap bitmap = BitmapFactory.decodeByteArray(encodeByte, 0, encodeByte.length);
            return bitmap;
        } catch(Exception e) {
            e.getMessage();
            return null;
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
//        Toast.makeText(getApplicationContext(),"location: " + l1 + "," + l2, Toast.LENGTH_LONG).show();
        LocationListener mlocListener = new MyLocationListener(this);
        mlocManager.requestLocationUpdates( LocationManager.GPS_PROVIDER, 5000, 10, mlocListener);

        l = mlocManager.getLastKnownLocation(LocationManager.GPS_PROVIDER);

        l = getLastBestLocation(mlocManager);


        // VER SI l1 y l2 son distintas de cero --> si es asi mandar Unknown
        return String.valueOf(l2)+";"+String.valueOf(l1);
    }

    private static Location getLastBestLocation(LocationManager mLocationManager) {
        Location locationGPS = mLocationManager.getLastKnownLocation(LocationManager.GPS_PROVIDER);
        Location locationNet = mLocationManager.getLastKnownLocation(LocationManager.NETWORK_PROVIDER);

        long GPSLocationTime = 0;
        if (null != locationGPS) { GPSLocationTime = locationGPS.getTime(); }

        long NetLocationTime = 0;

        if (null != locationNet) {
            NetLocationTime = locationNet.getTime();
        }

        if ( 0 < GPSLocationTime - NetLocationTime ) {
            return locationGPS;
        }
        else {
            return locationNet;
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
