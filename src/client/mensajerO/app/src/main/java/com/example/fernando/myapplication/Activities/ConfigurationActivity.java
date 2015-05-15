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
import android.widget.Toast;

import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Threads.ConfigPostAsyncTask;
import com.example.fernando.myapplication.R;

import java.io.File;
import java.io.FilenameFilter;

/**
 * Created by fernando on 10/04/15.
 */
public class ConfigurationActivity extends ActionBarActivity implements View.OnClickListener {

    ConfigPostAsyncTask configPost;

    RadioButton online;
    RadioButton offline;
    RadioButton out;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.configuration);

        Button button1 = (Button) findViewById(R.id.button1);
        button1.setOnClickListener(this);

        Button button2 = (Button) findViewById(R.id.button2);
        button2.setOnClickListener(this);

        offline = (RadioButton) findViewById(R.id.offline);
        out = (RadioButton) findViewById(R.id.out);
        online = (RadioButton) findViewById(R.id.online);
        offline.setOnClickListener(this);
        out.setOnClickListener(this);
        online.setOnClickListener(this);

        configPost = new ConfigPostAsyncTask();

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

            if (Constants.configOK.contains("Error")) {
                Toast.makeText(this, "Could't connect with server. Your changes won't be saved\nafter you Log Out", Toast.LENGTH_LONG).show();
            }

            if (Constants.signUpOk.compareTo("true") == 0) {
                Toast.makeText(this, "Changes saved properly", Toast.LENGTH_LONG).show();
                finish();
            } else {
                Toast.makeText(this, "Could't connect with server. Your changes won't be saved\nafter you Log Out", Toast.LENGTH_LONG).show();
                finish();
            }

        } else if (v.getId() == R.id.online) {
            offline.setChecked(false);
            out.setChecked(false);
        } else if (v.getId() == R.id.offline) {
            online.setChecked(false);
            out.setChecked(false);
        } else if (v.getId() == R.id.out) {
            offline.setChecked(false);
            online.setChecked(false);
        }
    }

    private String[] mFileList;
    private File mPath = new File(Environment.getExternalStorageDirectory() + "/Download");
    private String mChosenFile;
    private static final String FTYPE = ".jpg";
    private static final String FTYPE2 = ".png";
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
                    return filename.contains(FTYPE) || filename.contains(FTYPE2) || sel.isDirectory();
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
