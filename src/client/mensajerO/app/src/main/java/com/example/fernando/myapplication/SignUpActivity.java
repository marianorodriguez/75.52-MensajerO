package com.example.fernando.myapplication;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;

/**
 * Created by fernando on 10/04/15.
 */
public class SignUpActivity  extends ActionBarActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Tell the activity which XML layout is right
        setContentView(R.layout.activity);

//        Button button1 = (Button) findViewById(R.id.button1);
//        button1.setOnClickListener(this);
//
//        Button button2 = (Button) findViewById(R.id.button2);
//        button2.setOnClickListener(this);
//
//        Button button3 = (Button) findViewById(R.id.button3);
//        button3.setOnClickListener(this);

        // Enable the "Up" button for more navigation options
//        getActionBar().setDisplayHomeAsUpEnabled(true);
    }
}
