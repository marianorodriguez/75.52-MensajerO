package com.fiuba.tallerii.mensajer0.Activities;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.support.v4.graphics.drawable.RoundedBitmapDrawable;
import android.support.v4.graphics.drawable.RoundedBitmapDrawableFactory;
import android.support.v7.app.ActionBarActivity;
import android.util.Base64;
import android.util.Pair;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.ImageView;
import android.widget.RadioButton;
import android.widget.TextView;
import android.widget.Toast;

import com.fiuba.tallerii.mensajer0.Common.Constants;
import com.example.fernando.mensajerO.R;
import com.fiuba.tallerii.mensajer0.Threads.ConfigPostAsyncTask;
import com.fiuba.tallerii.mensajer0.Threads.GetUsersPostAsyncTask;
import com.fiuba.tallerii.mensajer0.Threads.SomethingForMePostAsyncTask;

import java.io.ByteArrayOutputStream;
import java.io.UnsupportedEncodingException;

public class ConfigurationActivity extends ActionBarActivity implements View.OnClickListener {

    ConfigPostAsyncTask configPost;

    RadioButton online;
    RadioButton offline;
    CheckBox checkin;

    ImageView profilePicture;

    private static int RESULT_LOAD_IMAGE = 1;
    SharedPreferences mSharedPref;

    Bitmap currentPicture;
    String currentStatus;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.configuration);

        getSupportActionBar().setDisplayShowCustomEnabled(true);
        getSupportActionBar().setDisplayShowTitleEnabled(false);
        LayoutInflater inflater = (LayoutInflater) getApplicationContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        View actionBar = inflater.inflate(R.layout.action_bar, null);
        getSupportActionBar().setCustomView(actionBar);

        ((TextView) actionBar.findViewById(R.id.actionBarTitle)).setText("SETTINGS");
        ((TextView) actionBar.findViewById(R.id.actionBarSubtitle)).setText(Constants.user.username);

        ((ImageView) actionBar.findViewById(R.id.actionBarIcon)).setImageResource(R.drawable.settings);


        ImageView cancelButton = (ImageView) findViewById(R.id.config_cancelButton);
        cancelButton.setOnClickListener(this);

        ImageView okButton = (ImageView) findViewById(R.id.config_okButton);
        okButton.setOnClickListener(this);

        profilePicture = (ImageView) findViewById(R.id.picture);

        profilePicture.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View arg0) {

                Intent i = new Intent(
                        Intent.ACTION_PICK,
                        android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);

                startActivityForResult(i, RESULT_LOAD_IMAGE);
            }
        });


        offline = (RadioButton) findViewById(R.id.offline);
        offline.setOnClickListener(this);
        online = (RadioButton) findViewById(R.id.online);
        online.setOnClickListener(this);
        checkin = (CheckBox) findViewById(R.id.config_checkBox);
        checkin.setOnClickListener(this);

        configPost = new ConfigPostAsyncTask();

        //setear los radio buttons segun el status del user
        setUserStatus();

        //guardo los estados antes de entrar a settings por si no se puede mandar al server
        currentStatus = Constants.user.status;
        currentPicture = Constants.user.profile_picture;

        mSharedPref = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);

        if (Constants.user.profile_picture != null) {

            RoundedBitmapDrawable img;
            img = RoundedBitmapDrawableFactory.create(getResources(), Constants.user.profile_picture);
            img.setCornerRadius(300f);
            profilePicture.setScaleType(ImageView.ScaleType.CENTER_CROP);
            profilePicture.setImageDrawable(img);
        }
    }

    private void setUserStatus() {
        //cargar de shared preferences al constants.user el staus (en LOGIN, en SIGN UP ya esta)
        if (Constants.user.status.compareTo("online")== 0) {
            online.setChecked(true);
            offline.setChecked(false);
        } else if (Constants.user.status.compareTo("offline")== 0) {
            online.setChecked(false);
            offline.setChecked(true);
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == RESULT_LOAD_IMAGE && resultCode == RESULT_OK && null != data) {
            Uri selectedImage = data.getData();
            String[] filePathColumn = { MediaStore.Images.Media.DATA };

            Cursor cursor = getContentResolver().query(selectedImage,
                    filePathColumn, null, null, null);
            cursor.moveToFirst();

            int columnIndex = cursor.getColumnIndex(filePathColumn[0]);
            String picturePath = cursor.getString(columnIndex);
            cursor.close();

//            ImageView imageView = (ImageView) findViewById(R.id.imageView);
            Bitmap imageSelected = BitmapFactory.decodeFile(picturePath);

            if (imageSelected == null) {
                Toast.makeText(this, "Problem happen while trying to open your picture.", Toast.LENGTH_SHORT).show();
                return;
            } else {

                profilePicture.setImageBitmap(BitmapFactory.decodeFile(picturePath));

                Constants.user.profile_picture = BitmapFactory.decodeFile(picturePath);

                SharedPreferences.Editor e = mSharedPref.edit();
                e.putString(Constants.user.username+"profile_picture", setPicture(Constants.user.profile_picture));
                e.commit();

                RoundedBitmapDrawable img;
                img = RoundedBitmapDrawableFactory.create(getResources(), Constants.user.profile_picture);
                img.setCornerRadius(300f);
                profilePicture.setScaleType(ImageView.ScaleType.CENTER_CROP);
                profilePicture.setImageDrawable(img);

            }
        }
    }

    private String setPicture(Bitmap pictureBitmap) {

        ByteArrayOutputStream baos = new  ByteArrayOutputStream();
        pictureBitmap.compress(Bitmap.CompressFormat.PNG, 100, baos);
        byte [] b=baos.toByteArray();
        String temp = Base64.encodeToString(b, Base64.DEFAULT);
        temp = temp.replaceAll("(?:\\r\\n|\\n\\r|\\n|\\r)", "");

        return temp;
    }

    @Override
    protected void onResume() {
        super.onResume();
        Constants.SomethingForMePostAsyncTaskFinish = true;
        Constants.GetUsersPostAsyncTaskFinish = true;
    }

    @Override
    public void onClick(View v) {

        if (v.getId() == R.id.config_cancelButton) {
            //Cancel button
            // seteo al user los valores que tenia antes de entrar
            SharedPreferences.Editor e = mSharedPref.edit();
            Constants.user.profile_picture = currentPicture;
            e.putString(Constants.user.username+"profile_picture", setPicture(currentPicture));
            profilePicture.setImageBitmap(Constants.user.profile_picture);

            Constants.user.status = currentStatus;
            e.putString(Constants.user.username+"status", currentStatus);
            e.commit();
            setUserStatus();

            finish();

        } else if (v.getId() == R.id.config_okButton) {
            //Done button

            String package_ = Constants.packager.wrap("setConfig", Constants.user);

            configPost.execute(new Pair<Context, String>(this, package_),
                    new Pair<Context, String>(this, Constants.setConfigUrl),
                    new Pair<Context, String>(this, "post"));

            int timeOut = 0;
            while (Constants.configOK.compareTo("") == 0) {
                try {
                    Thread.sleep(1000);
                    timeOut++;
                    if (timeOut == 4)
                        Constants.logInOk = "Error";
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }

            if (Constants.configOK.compareTo("true") == 0) {
                Toast.makeText(this, "Changes saved properly.", Toast.LENGTH_SHORT).show();
                Constants.configOK = "";
                finish();

                ((TextView) Constants.chatsHallActionBar.findViewById(R.id.actionBarSubtitle)).setText("Status: "+Constants.user.status);

                RoundedBitmapDrawable img;
                img = RoundedBitmapDrawableFactory.create(getResources(), Constants.user.profile_picture);
                img.setCornerRadius(300f);
                ((ImageView) Constants.chatsHallActionBar.findViewById(R.id.actionBarIcon)).setImageDrawable(img);

            } else {
                Toast.makeText(this, "Couldn't connect with server. Your changes won't be saved.", Toast.LENGTH_LONG).show();
                Constants.configOK = "";
                configPost = new ConfigPostAsyncTask();
            }

        } else if (v.getId() == R.id.online) {
            changeUserStatus(0);
            offline.setChecked(false);
        } else if (v.getId() == R.id.offline) {
            changeUserStatus(1);
            online.setChecked(false);
        }
    }

    private void changeUserStatus(int i) {
        SharedPreferences.Editor e = mSharedPref.edit();

        switch (i) {
            case 0:
                Constants.user.status = "online";
                e.putString(Constants.user.username+"status", "online");
                break;
            case 1:
                Constants.user.status = "offline";
                e.putString(Constants.user.username+"status", "offline");
                break;
        }
        e.commit();
    }

    public String wrap(Bitmap profilePicture) {

        byte[] data;
        try {
            data = profilePicture.toString().getBytes("UTF-8");
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
            return null;
        }

        String packageEncoded = Base64.encodeToString(data, Base64.NO_WRAP);
        packageEncoded = packageEncoded.replaceAll("(?:\\r\\n|\\n\\r|\\n|\\r)", "");

        return packageEncoded;
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (configPost != null)
            configPost.cancel(true);

        Constants.GetUsersPostAsyncTaskFinish = false;
        Constants.SomethingForMePostAsyncTaskFinish = false;
        ChatsHallActivity.somethingForMePost = new SomethingForMePostAsyncTask();
        ChatsHallActivity.somethingForMePost.execute(new Pair<Context, String>(this, ChatsHallActivity.package_),
                new Pair<Context, String>(this, Constants.somethingForMeUrl),
                new Pair<Context, String>(this, "get"));
        ChatsHallActivity.getUsersPost = new GetUsersPostAsyncTask();
        ChatsHallActivity.getUsersPost.execute(new Pair<Context, String>(this, ChatsHallActivity.package_),
                new Pair<Context, String>(this, Constants.usersUrl),
                new Pair<Context, String>(this, "get"));
    }

}
