package com.example.fernando.myapplication.Activities;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.View;
import android.widget.Button;

import com.example.fernando.myapplication.R;

/**
 * Created by fernando on 10/04/15.
 */
public class UsersActivity extends ActionBarActivity implements View.OnClickListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Tell the login which XML layout is right
        setContentView(R.layout.users);

        Button button1 = (Button) findViewById(R.id.button1);
        button1.setOnClickListener(this);

        Button button2 = (Button) findViewById(R.id.button2);
        button2.setOnClickListener(this);

        // Enable the "Up" button for more navigation options
//        getActionBar().setDisplayHomeAsUpEnabled(true);
    }

    @Override
    public void onClick(View v) {

        if (v.getId() == R.id.button1) {

//            // create an Intent to take you over to a new DetailActivity
//            Intent chatsHall = new Intent(this, ChatsHallActivity.class);
//
//            // pack away the data about the cover
//            // into your Intent before you head out
//            chatsHall.putExtra("coverID", "undato");
//
//            // TODO: add any other data you'd like as Extras
//
//            // start the next Activity using your prepared Intent
//            startActivity(chatsHall);
            finish();

        } else if (v.getId() == R.id.button2) {

            // create an Intent to take you over to a new DetailActivity
            Intent chat = new Intent(this, ChatActivity.class);

            // pack away the data about the cover
            // into your Intent before you head out
            chat.putExtra("coverID", "undato");

            // TODO: add any other data you'd like as Extras

            // start the next Activity using your prepared Intent
            startActivity(chat);

        }/* else if (v.getId() == R.id.button3) {

            // create an Intent to take you over to a new DetailActivity
            Intent config = new Intent(this, ConfigurationActivity.class);

            // pack away the data about the cover
            // into your Intent before you head out
            config.putExtra("coverID", "undato");

            // TODO: add any other data you'd like as Extras

            // start the next Activity using your prepared Intent
            startActivity(config);

        } else if (v.getId() == R.id.button4) { // button4

            // borrar datos de shared preferences
            finish();
        }*/
    }
}
