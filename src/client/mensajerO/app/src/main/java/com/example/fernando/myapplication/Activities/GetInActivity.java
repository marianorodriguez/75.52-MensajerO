package com.example.fernando.myapplication.Activities;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.location.LocationManager;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Base64;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;

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

        Button mainButton = (Button) findViewById(R.id.backtologin);
        mainButton.setOnClickListener(this);

        ipContainer = (EditText) findViewById(R.id.ipedittext);

//        setContentView(R.layout.users);

//        LinearLayout linearLayout = (LinearLayout) findViewById(R.id.users);
//
////        Button send = (Button) findViewById(R.id.sendButton);
////        send.setOnClickListener(new View.OnClickListener() {
////
////            @Override
////            public void onClick(View v) {
////                ScrollView cont = (ScrollView) findViewById(R.id.scrollView);
////                cont.fullScroll(ScrollView.FOCUS_DOWN);
////
////            }
////        });
//
//        LayoutInflater vi = (LayoutInflater) getApplicationContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
//        final View message = vi.inflate(R.layout.user_item_chats, null);
//        View message2 = vi.inflate(R.layout.user_item_chats, null);
//        View message3 = vi.inflate(R.layout.user_item_chats, null);
//        View message4 = vi.inflate(R.layout.user_item_chats, null);
//        View message5 = vi.inflate(R.layout.user_item_chats, null);
//        View message6 = vi.inflate(R.layout.user_item_chats, null);
//        View message7 = vi.inflate(R.layout.user_item_chats, null);
//        View message8 = vi.inflate(R.layout.user_item_chats, null);
//
//        ((TextView) message.findViewById(R.id.userItemData)).setText("fer");
//        ((TextView) message.findViewById(R.id.userItemData)).setText("2");
//        ((TextView) message.findViewById(R.id.userItemData)).setText("3");
//
//
//        message.setOnClickListener(this);
//        message2.setOnClickListener(this);
//        message3.setOnClickListener(this);
//
////        message.setOnClickListener(new View.OnClickListener() {
////
////            @Override
////            public void onClick(View v) {
////                ((ImageView) message.findViewById(R.id.userItemImage)).setVisibility(View.INVISIBLE);
////
////            });
////        }
//
//        message8.setVisibility(View.VISIBLE);
//
////        ((TextView)message7.findViewById(R.id.myText)).setText("the lastfsdf\n\nsdfsDFSDssssssssss  FSDSDFSD one");
//
////        message.findViewById(R.id.othersMessage).setVisibility(View.INVISIBLE);
////        message3.findViewById(R.id.myMessage).setVisibility(View.INVISIBLE);
//
//        linearLayout.setOrientation(LinearLayout.VERTICAL);
////        RelativeLayout.LayoutParams newrlp = new RelativeLayout()
//        linearLayout.addView(message, 0, new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.FILL_PARENT, 200));
//        linearLayout.addView(message2, 1, new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.FILL_PARENT, 200));
//        linearLayout.addView(message3, 0, new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.FILL_PARENT, 200));
//        linearLayout.addView(message4, 3, new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.FILL_PARENT, 200));
//        linearLayout.addView(message5, 4, new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.FILL_PARENT, 200));
//        linearLayout.addView(message6, 5, new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.FILL_PARENT, 200));
////        linearLayout.addView(message6, 6, new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.FILL_PARENT, RelativeLayout.LayoutParams.WRAP_CONTENT));
//        linearLayout.addView(message7, 6, new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.FILL_PARENT, 200));
//        linearLayout.addView(message8, 7, new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.FILL_PARENT, 200));
//


//        linearLayout.addView(message);
//        linearLayout.addView(message);


//
//        v.findViewById(R.id.userItemImage).setVisibility(View.INVISIBLE);
//        return;


//                cont.addView(linearLayout);
//        cont.addView(linearLayout, 0, new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.FILL_PARENT, RelativeLayout.LayoutParams.FILL_PARENT));

//        send.callOnClick();
//        send.performClick();
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

//    @TargetApi(Build.VERSION_CODES.JELLY_BEAN)
//    public void pushNotification() {
//        NotificationCompat.Builder mBuilder =
//                new NotificationCompat.Builder(this)
//                        .setSmallIcon(R.drawable.ic_launcher)
//                        .setContentTitle("My notification")
//                        .setContentText("Hello World!");
//
//        Notification notification = mBuilder.build();
//// Creates an explicit intent for an Activity in your app
//        Intent resultIntent = new Intent(this, LogInActivity.class);
//
//// The stack builder object will contain an artificial back stack for the
//// started Activity.
//// This ensures that navigating backward from the Activity leads out of
//// your application to the Home screen.
//        TaskStackBuilder stackBuilder = TaskStackBuilder.create(this);
//// Adds the back stack for the Intent (but not the Intent itself)
//        stackBuilder.addParentStack(LogInActivity.class);
//// Adds the Intent that starts the Activity to the top of the stack
//        stackBuilder.addNextIntent(resultIntent);
//        PendingIntent resultPendingIntent =
//                stackBuilder.getPendingIntent(
//                        0,
//                        PendingIntent.FLAG_UPDATE_CURRENT
//                );
//        mBuilder.setContentIntent(resultPendingIntent);
//        NotificationManager mNotificationManager =
//                (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
//// mId allows you to update the notification later on.
//
//        mNotificationManager.notify(1, mBuilder.build());
//
//        notification.flags |= Notification.FLAG_AUTO_CANCEL;
//
//        mNotificationManager.notify(0, notification);
//        // LUEGO PARA ACTUALIZAR EL TEXTO !!
////        mBuilder.setContentText("fer\nljkjkj\nkljkj\n\n ferrr");
////        mNotificationManager.notify(1 , mBuilder.build());
//    }

    @Override
    public void onClick(View v) {

        //CHEQUEAR EL FORMATO DE LA IP y setear Constants.ip

        EditText ip = (EditText) findViewById(R.id.ipedittext);
        if (ip.getText().toString().isEmpty()) {
            Toast.makeText(this, "Enter server's ip!", Toast.LENGTH_SHORT).show();
            return;
        }

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