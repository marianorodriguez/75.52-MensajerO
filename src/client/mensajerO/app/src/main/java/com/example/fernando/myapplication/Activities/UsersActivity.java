package com.example.fernando.myapplication.Activities;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
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

        Button button2 = (Button) findViewById(R.id.button2);
        button2.setOnClickListener(this);

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.users_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent login in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.chatsHall) {

            finish();
            return true;

        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    public void onClick(View v) {

        if (v.getId() == R.id.button2) {

            // create an Intent to take you over to a new DetailActivity
            Intent chat = new Intent(this, ChatActivity.class);

            // pack away the data about the cover
            // into your Intent before you head out
            chat.putExtra("coverID", "undato");

            // TODO: add any other data you'd like as Extras

            // start the next Activity using your prepared Intent
            startActivity(chat);

        }
    }
}
