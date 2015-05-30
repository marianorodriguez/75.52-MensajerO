package com.example.fernando.myapplication.Activities;

import android.annotation.TargetApi;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.TaskStackBuilder;
import android.content.Context;
import android.content.Intent;
import android.location.Criteria;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Build;
import android.os.Bundle;
import android.support.v4.app.NotificationCompat;
import android.support.v7.app.ActionBarActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.R;

public class GetInActivity extends ActionBarActivity implements View.OnClickListener {

    private LocationManager locationManager;
    private String provider;

    EditText ipContainer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.getin);

//        LocationManager mlocManager = (LocationManager)getSystemService(Context.LOCATION_SERVICE);
//        boolean net = mlocManager.isProviderEnabled(LocationManager.GPS_PROVIDER);
//        Location l = null;
//        if(net)
//            l= mlocManager.getLastKnownLocation(LocationManager.GPS_PROVIDER);
//
//        double l1 = 0;
//        double l2 = 0;
//        if(l!=null)
//        {
//            l1 = l.getLongitude();
//            l2 = l.getLatitude();
//        }
//        Toast.makeText(getApplicationContext(),l1+".."+l2, Toast.LENGTH_LONG).show();
//        LocationListener mlocListener = new MyLocationListener();
//        mlocManager.requestLocationUpdates( LocationManager.GPS_PROVIDER, 0, 0, mlocListener);

        Button mainButton = (Button) findViewById(R.id.button1);
        mainButton.setOnClickListener(this);

        ipContainer = (EditText) findViewById(R.id.editText2);
    }

    public class MyLocationListener implements LocationListener
    {
        @Override
        public void onLocationChanged(Location loc) {

            loc.getLatitude();
            loc.getLongitude();
            String Text = "My current location is: "+
                    "Latitud = " + loc.getLatitude() +
                    "Longitud = " + loc.getLongitude();

            Toast.makeText( getApplicationContext(),
                    Text,
                    Toast.LENGTH_SHORT).show();
        }

        @Override
        public void onProviderDisabled(String provider) {

            Toast.makeText( getApplicationContext(),
                    "Gps Disabled",
                    Toast.LENGTH_SHORT ).show();
        }

        @Override
        public void onProviderEnabled(String provider)
        {

            Toast.makeText( getApplicationContext(),
                    "Gps Enabled",
                    Toast.LENGTH_SHORT).show();
        }

        @Override
        public void onStatusChanged(String provider, int status, Bundle extras)
        {}
    }

    @TargetApi(Build.VERSION_CODES.JELLY_BEAN)
    public void pushNotification() {
        NotificationCompat.Builder mBuilder =
                new NotificationCompat.Builder(this)
                        .setSmallIcon(R.drawable.ic_launcher)
                        .setContentTitle("My notification")
                        .setContentText("Hello World!");

        Notification notification = mBuilder.build();
// Creates an explicit intent for an Activity in your app
        Intent resultIntent = new Intent(this, LogInActivity.class);

// The stack builder object will contain an artificial back stack for the
// started Activity.
// This ensures that navigating backward from the Activity leads out of
// your application to the Home screen.
        TaskStackBuilder stackBuilder = TaskStackBuilder.create(this);
// Adds the back stack for the Intent (but not the Intent itself)
        stackBuilder.addParentStack(LogInActivity.class);
// Adds the Intent that starts the Activity to the top of the stack
        stackBuilder.addNextIntent(resultIntent);
        PendingIntent resultPendingIntent =
                stackBuilder.getPendingIntent(
                        0,
                        PendingIntent.FLAG_UPDATE_CURRENT
                );
        mBuilder.setContentIntent(resultPendingIntent);
        NotificationManager mNotificationManager =
                (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
// mId allows you to update the notification later on.

        mNotificationManager.notify(1, mBuilder.build());

        notification.flags |= Notification.FLAG_AUTO_CANCEL;

        mNotificationManager.notify(0, notification);
        // LUEGO PARA ACTUALIZAR EL TEXTO !!
//        mBuilder.setContentText("fer\nljkjkj\nkljkj\n\n ferrr");
//        mNotificationManager.notify(1 , mBuilder.build());
    }

    @Override
    public void onClick(View v) {

        //CHEQUEAR EL FORMATO DE LA IP y setear Constants.ip
        Constants.ipServer = ipContainer.getText().toString();

        Intent logIn = new Intent(this, LogInActivity.class);
        startActivity(logIn);
        finish();

    }
}