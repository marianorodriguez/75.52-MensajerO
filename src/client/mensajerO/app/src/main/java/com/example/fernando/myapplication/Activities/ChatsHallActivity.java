package com.example.fernando.myapplication.Activities;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
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
    private static final String PREF_NAME = "name";
    private static final String PREF_PASS = "password";

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
            String p = mSharedPreferences.getString(PREF_PASS, "");
            Toast.makeText(getApplicationContext(), "Welcome, " + username + p + "!", Toast.LENGTH_LONG).show();

            Button button2 = (Button) findViewById(R.id.button2);
            button2.setOnClickListener(this);

        }

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.chatshall_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent login in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.users) {

            // create an Intent to take you over to a new DetailActivity
            Intent users = new Intent(this, UsersActivity.class);

            // pack away the data about the cover
            // into your Intent before you head out
            users.putExtra("coverID", "undato");

            // TODO: add any other data you'd like as Extras

            // start the next Activity using your prepared Intent
            startActivity(users);
            return true;

        } else if (id == R.id.logOut) {

            // Access the device's key-value storage
            mSharedPreferences = getSharedPreferences(PREFS, MODE_PRIVATE);

            SharedPreferences.Editor e = mSharedPreferences.edit();
            e.clear();
//            e.putString(PREF_NAME, "");
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
            return true;

        } else if (id == R.id.settings) {

            // create an Intent to take you over to a new DetailActivity
            Intent config = new Intent(this, ConfigurationActivity.class);

            // pack away the data about the cover
            // into your Intent before you head out
            config.putExtra("coverID", "undato");

            // TODO: add any other data you'd like as Extras

            // start the next Activity using your prepared Intent
            startActivity(config);
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
