package com.example.fernando.myapplication.Activities;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.util.Pair;
import android.view.View;
import android.widget.Button;
import android.widget.RadioButton;

import com.example.fernando.myapplication.Threads.ServletPostAsyncTask;
import com.example.fernando.myapplication.R;

import java.io.File;
import java.io.FilenameFilter;

/**
 * Created by fernando on 10/04/15.
 */
public class ConfigurationActivity extends ActionBarActivity implements View.OnClickListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Tell the login which XML layout is right
        setContentView(R.layout.configuration);

        Button button1 = (Button) findViewById(R.id.button1);
        button1.setOnClickListener(this);

        Button button2 = (Button) findViewById(R.id.button2);
        button2.setOnClickListener(this);

        // PARA AGARRAR LA FOTO DEL FILE SYSTEM !!
//        loadFileList();
//        onCreateDialog(1000);

    }

    @Override
    public void onClick(View v) {

        if (v.getId() == R.id.button1) {
            //Cancel button
            finish();
        } else if (v.getId() == R.id.button2 ) {
            //Done button

            //ARMAR EL PAQETE CORRESPONDIENTE CON FOTO DE USER
            // HACER EL POST
            new ServletPostAsyncTask().execute(new Pair<Context, String>(this, "packageToServer"),
                    new Pair<Context, String>(this, "http://10.0.2.2:8080/config"),
                    new Pair<Context, String>(this, "post"));
            boolean ok = true;
            if (ok) {
//                TOCAR CONSTANTS
                finish();
            } else {
                // tirar toast de que no se pudo conectar con el server, verifique su conexion
            }

        } else if (v.getId() == R.id.online) {
            RadioButton offline = (RadioButton) findViewById(R.id.offline);
            RadioButton out = (RadioButton) findViewById(R.id.out);
            offline.setChecked(false);
            out.setChecked(false);
        } else if (v.getId() == R.id.offline) {
            RadioButton online = (RadioButton) findViewById(R.id.online);
            RadioButton out = (RadioButton) findViewById(R.id.out);
            online.setChecked(false);
            out.setChecked(false);
        } else if (v.getId() == R.id.out) {
            RadioButton offline = (RadioButton) findViewById(R.id.offline);
            RadioButton online = (RadioButton) findViewById(R.id.online);
            offline.setChecked(false);
            online.setChecked(false);
        }
    }

    private String[] mFileList;
    private File mPath = new File(Environment.getExternalStorageDirectory() + "/Download");
    private String mChosenFile;
    private static final String FTYPE = ".apk";
    private static final int DIALOG_LOAD_FILE = 1000;

    private void loadFileList() {
        try {
            mPath.mkdirs();
        }
        catch(SecurityException e) {
            Log.e("", "unable to write on the sd card " + e.toString());
        }
        if(mPath.exists()) {
            FilenameFilter filter = new FilenameFilter() {

                @Override
                public boolean accept(File dir, String filename) {
                    File sel = new File(dir, filename);
                    return filename.contains(FTYPE) || sel.isDirectory();
                }

            };
            mFileList = mPath.list(filter);
        }
        else {
            mFileList= new String[0];
        }
    }

    protected Dialog onCreateDialog(int id) {
        Dialog dialog = null;
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        switch(id) {
            case DIALOG_LOAD_FILE:
                builder.setTitle("Choose your file");
                if(mFileList == null) {
                    Log.e("", "Showing file picker before loading the file list");
                    dialog = builder.create();
                    return dialog;
                }
                builder.setItems(mFileList, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {
                        mChosenFile = mFileList[which];
                        //you can do stuff with the file here too
                    }
                });
                break;
        }
        dialog = builder.show();
        return dialog;
    }

}
