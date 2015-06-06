package com.example.fernando.myapplication.Activities;

import android.annotation.TargetApi;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.TaskStackBuilder;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.location.LocationManager;
import android.os.Build;
import android.os.Bundle;
import android.support.v4.app.NotificationCompat;
import android.support.v7.app.ActionBarActivity;
import android.util.Base64;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.R;

import java.io.ByteArrayOutputStream;

public class GetInActivity extends ActionBarActivity implements View.OnClickListener {

    private LocationManager locationManager;
    private String provider;

    EditText ipContainer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.getin);

        Button mainButton = (Button) findViewById(R.id.getinbutton);
        mainButton.setOnClickListener(this);

        ipContainer = (EditText) findViewById(R.id.ipedittext);
    }

    private Bitmap setPicture(Bitmap pictureBitmap) {

        ByteArrayOutputStream baos = new  ByteArrayOutputStream();
        pictureBitmap.compress(Bitmap.CompressFormat.PNG, 100, baos);
        byte [] b = baos.toByteArray();
        String pictureString = Base64.encodeToString(b, Base64.DEFAULT);
        pictureString = pictureString.replaceAll("(?:\\r\\n|\\n\\r|\\n|\\r)", "");

        Bitmap bitmap;
        try {
            byte [] encodeByte = Base64.decode(pictureString, Base64.DEFAULT);
            bitmap = BitmapFactory.decodeByteArray(encodeByte, 0, encodeByte.length);

        } catch(Exception e) {
            e.getMessage();
            return null;
        }
        baos = new  ByteArrayOutputStream();
        bitmap.compress(Bitmap.CompressFormat.PNG, 100, baos);
        b = baos.toByteArray();
        String pictureString2 = Base64.encodeToString(b, Base64.DEFAULT);
        pictureString2 = pictureString2.replaceAll("(?:\\r\\n|\\n\\r|\\n|\\r)", "");
        int a = 2;

        return bitmap;
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
        SharedPreferences mSharedPref = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);
        SharedPreferences.Editor e = mSharedPref.edit();
        e.putString("ipServer", ipContainer.getText().toString());
        e.commit();
        Constants.setIp(ipContainer.getText().toString());

        Intent logIn = new Intent(this, LogInActivity.class);
        startActivity(logIn);
        finish();

    }
}