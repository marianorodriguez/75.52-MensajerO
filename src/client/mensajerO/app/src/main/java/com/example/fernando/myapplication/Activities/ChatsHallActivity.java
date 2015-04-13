package com.example.fernando.myapplication.Activities;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.example.fernando.myapplication.R;

/**
 * Created by fernando on 10/04/15.
 */
public class ChatsHallActivity extends ActionBarActivity implements View.OnClickListener {
    SharedPreferences mSharedPreferences;
    private static final String PREFS = "prefs";
    private static final String PREF_NAME = "Fer";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Tell the login which XML layout is right
        setContentView(R.layout.chatshall);

        mSharedPreferences = getSharedPreferences(PREFS, MODE_PRIVATE);
        if (mSharedPreferences.getString(PREF_NAME, "").isEmpty()) {
            Intent getIn = new Intent(this, GetInActivity.class);

            // pack away the data about the cover
            // into your Intent before you head out
            getIn.putExtra("coverID", "undato");

            // TODO: add any other data you'd like as Extras

            // start the next Activity using your prepared Intent
            startActivity(getIn);
            finish();
        } else {
            String username = mSharedPreferences.getString(PREF_NAME, "");
            Toast.makeText(getApplicationContext(), "Welcome, " + username + "!", Toast.LENGTH_LONG).show();

            Button button1 = (Button) findViewById(R.id.button1);
            button1.setOnClickListener(this);

            Button button2 = (Button) findViewById(R.id.button2);
            button2.setOnClickListener(this);

            Button button3 = (Button) findViewById(R.id.button3);
            button3.setOnClickListener(this);

            Button button4 = (Button) findViewById(R.id.button4);
            button4.setOnClickListener(this);
        }

        // Enable the "Up" button for more navigation options
//        getActionBar().setDisplayHomeAsUpEnabled(true);
    }

    @Override
    public void onClick(View v) {

        if (v.getId() == R.id.button1) {

            // create an Intent to take you over to a new DetailActivity
            Intent users = new Intent(this, UsersActivity.class);

            // pack away the data about the cover
            // into your Intent before you head out
            users.putExtra("coverID", "undato");

            // TODO: add any other data you'd like as Extras

            // start the next Activity using your prepared Intent
            startActivity(users);


        } else if (v.getId() == R.id.button2) {

            // create an Intent to take you over to a new DetailActivity
            Intent chat = new Intent(this, ChatActivity.class);

            // pack away the data about the cover
            // into your Intent before you head out
            chat.putExtra("coverID", "undato");

            // TODO: add any other data you'd like as Extras

            // start the next Activity using your prepared Intent
            startActivity(chat);

        } else if (v.getId() == R.id.button3) {

            // create an Intent to take you over to a new DetailActivity
            Intent config = new Intent(this, ConfigurationActivity.class);

            // pack away the data about the cover
            // into your Intent before you head out
            config.putExtra("coverID", "undato");

            // TODO: add any other data you'd like as Extras

            // start the next Activity using your prepared Intent
            startActivity(config);

        } else if (v.getId() == R.id.button4){ // button4

            // Access the device's key-value storage
            mSharedPreferences = getSharedPreferences(PREFS, MODE_PRIVATE);

            SharedPreferences.Editor e = mSharedPreferences.edit();
            e.putString(PREF_NAME, "");
            e.commit();

            // create an Intent to take you over to a new DetailActivity
            Intent login = new Intent(this, LogInActivity.class);

            // pack away the data about the cover
            // into your Intent before you head out
            login.putExtra("coverID", "undato");

            // TODO: add any other data you'd like as Extras

            // start the next Activity using your prepared Intent
            startActivity(login);

            finish();
        }
    }
}
