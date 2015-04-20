package com.example.fernando.myapplication.Activities;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;

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

//        TextView mainTextView = (TextView) findViewById(R.id.textView);
//        mainTextView.setText("Set in Java!\n fer \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n fer");

    }

}
