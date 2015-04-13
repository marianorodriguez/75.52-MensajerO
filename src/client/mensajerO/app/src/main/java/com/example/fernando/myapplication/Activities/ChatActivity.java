package com.example.fernando.myapplication.Activities;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.View;
import android.widget.Button;

import com.example.fernando.myapplication.R;

/**
 * Created by fernando on 10/04/15.
 */
public class ChatActivity extends ActionBarActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Tell the login which XML layout is right
        setContentView(R.layout.chat);


        // Enable the "Up" button for more navigation options
//        getActionBar().setDisplayHomeAsUpEnabled(true);
    }
}
