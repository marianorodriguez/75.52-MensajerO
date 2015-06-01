package com.example.fernando.myapplication.Activities;

import android.app.ActionBar;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.support.v7.app.ActionBarActivity;
import android.util.Base64;
import android.util.Log;
import android.util.Pair;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.RadioButton;
import android.widget.Toast;

import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Common.User;
import com.example.fernando.myapplication.Threads.ConfigPostAsyncTask;
import com.example.fernando.myapplication.R;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FilenameFilter;
import java.io.UnsupportedEncodingException;

/**
 * Created by fernando on 10/04/15.
 */
public class ConfigurationActivity extends ActionBarActivity implements View.OnClickListener {

    ConfigPostAsyncTask configPost;

    RadioButton online;
    RadioButton offline;
    RadioButton out;

    ImageView profilePicture;

    private static int RESULT_LOAD_IMAGE = 1;
    SharedPreferences mSharedPref;

    Bitmap currentPicture;
    String currentStatus;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.configuration);

        Button button1 = (Button) findViewById(R.id.button1);
        button1.setOnClickListener(this);

        Button button2 = (Button) findViewById(R.id.button2);
        button2.setOnClickListener(this);

        Button buttonLoadImage = (Button) findViewById(R.id.button);
        buttonLoadImage.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View arg0) {

                Intent i = new Intent(
                        Intent.ACTION_PICK,
                        android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);

                startActivityForResult(i, RESULT_LOAD_IMAGE);
            }
        });

        profilePicture = (ImageView) findViewById(R.id.imageView);

        offline = (RadioButton) findViewById(R.id.offline);
        offline.setOnClickListener(this);
        out = (RadioButton) findViewById(R.id.out);
        out.setOnClickListener(this);
        online = (RadioButton) findViewById(R.id.online);
        online.setOnClickListener(this);

        configPost = new ConfigPostAsyncTask();

        //setear los radio buttons segun el status del user
        setUserStatus();

        //guardo los estados antes de entrar a settings por si no se puede mandar al server
        currentStatus = Constants.user.status;
        currentPicture = Constants.user.profile_picture;

        mSharedPref = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);

        if (Constants.user.profile_picture != null) {

            profilePicture.setImageBitmap(Constants.user.profile_picture);

            float scaleRatio = getResources().getDisplayMetrics().density;
            int dps = 150;
            int pixels = (int) (dps * scaleRatio + 0.5f);

            profilePicture.getLayoutParams().height = pixels; // OR
            profilePicture.getLayoutParams().width = pixels;
        }
    }

    private void setUserStatus() {
        //cargar de shared preferences al constants.user el staus (en LOGIN, en SIGN UP ya esta)
        if (Constants.user.status.compareTo("online")== 0) {
            online.setChecked(true);
            offline.setChecked(false);
            out.setChecked(false);
        } else if (Constants.user.status.compareTo("offline")== 0) {
            online.setChecked(false);
            offline.setChecked(true);
            out.setChecked(false);
        } else if (Constants.user.status.compareTo("out")== 0) {
            online.setChecked(false);
            offline.setChecked(false);
            out.setChecked(true);
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
                Toast.makeText(this, "Problem happen while trying to open your picture", Toast.LENGTH_LONG).show();
                return;
            } else {

                profilePicture.setImageBitmap(BitmapFactory.decodeFile(picturePath));

                Constants.user.profile_picture = BitmapFactory.decodeFile(picturePath);

                SharedPreferences.Editor e = mSharedPref.edit();
                e.putString(Constants.user.username+"profile_picture", setPicture(Constants.user.profile_picture));
                e.commit();

                float scaleRatio = getResources().getDisplayMetrics().density;
                int dps = 150;
                int pixels = (int) (dps * scaleRatio + 0.5f);

                profilePicture.getLayoutParams().height = pixels; // OR
                profilePicture.getLayoutParams().width = pixels;
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
    public void onClick(View v) {

        if (v.getId() == R.id.button1) {
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

        } else if (v.getId() == R.id.button2 ) {
            //Done button

            String package_ = Constants.packager.wrap("setConfig", Constants.user);

            configPost.execute(new Pair<Context, String>(this, package_),
                    new Pair<Context, String>(this, Constants.setConfigUrl),
                    new Pair<Context, String>(this, "post"));

            while (Constants.configOK.compareTo("") == 0) {
                try {
                    Thread.sleep(10);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }

            if (Constants.configOK.contains("Error") ) {
                Toast.makeText(this, "Could't connect with server. Your changes won't be saved.", Toast.LENGTH_LONG).show();
                Constants.configOK = "";
                configPost = new ConfigPostAsyncTask();
            }

            if (Constants.configOK.compareTo("true") == 0) {
                Toast.makeText(this, "Changes saved properly", Toast.LENGTH_LONG).show();
                Constants.configOK = "";
                finish();

            } else {
                Toast.makeText(this, "Could't connect with server. Your changes won't be saved.", Toast.LENGTH_LONG).show();
                Constants.configOK = "";
                configPost = new ConfigPostAsyncTask();
            }

        } else if (v.getId() == R.id.online) {
            changeUserStatus(0);
            offline.setChecked(false);
            out.setChecked(false);
        } else if (v.getId() == R.id.offline) {
            changeUserStatus(1);
            online.setChecked(false);
            out.setChecked(false);
        } else if (v.getId() == R.id.out) {
            changeUserStatus(2);
            offline.setChecked(false);
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
            case 2:
                Constants.user.status = "out";
                e.putString(Constants.user.username+"status", "out");
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
    }

}
