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

import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.R;

import java.util.logging.Handler;

/**
 * Created by fernando on 10/04/15.
 */
public class ChatsHallActivity extends ActionBarActivity implements View.OnClickListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.chatshall);

        Constants.mSharedPreferences = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);

        if (Constants.mSharedPreferences.getString(Constants.PREF_NAME, "").isEmpty()) {

            Intent getIn = new Intent(this, GetInActivity.class);
            startActivity(getIn);
            finish();

        } else {

            String username = Constants.mSharedPreferences.getString(Constants.PREF_NAME, "");
            Toast.makeText(getApplicationContext(), "Welcome, " + username + "!", Toast.LENGTH_LONG).show();

            Button button2 = (Button) findViewById(R.id.button2);
            button2.setOnClickListener(this);

            // tirar un hilo que llame a something for me (si llega algo tirar pop up)
            // tirar un hilo que llame a users
            // tirar hilo que vea si hay chats nuevos en la lista de chats y si lo hay
            // o si hay mensaje nuevo lo muestre y los ordene

            // si los hilos responden, desparsear
            // actualizar listas de chats y users (con hilos)

            // sino responde --> no conexxion toast

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
        int id = item.getItemId();

        if (id == R.id.users) {
            Intent users = new Intent(this, UsersActivity.class);
            startActivity(users);
            return true;

        } else if (id == R.id.logOut) {

            Constants.mSharedPreferences = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);
            SharedPreferences.Editor e = Constants.mSharedPreferences.edit();
            e.clear();
            e.commit();

            // GUARDAR CHATS en archivo con nombre de username (o crear el json
            // y mandar al server que lo
            // guarde porque si abre en otro device no va a estar)
            // SI LO HACE ON DESTROY NO HACERLO ACA ESTO

            Intent login = new Intent(this, LogInActivity.class);
            startActivity(login);
            finish();
            return true;

        } else if (id == R.id.settings) {

            Intent config = new Intent(this, ConfigurationActivity.class);
            startActivity(config);
            return true;

        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onDestroy() { // supuestamente llama a este metodo cuando hace FINISH
        super.onDestroy();
        // The activity is about to be destroyed.

        // GUARDAR CHATS en archivo con nombre de username (o crear el json
        // y mandar al server que lo
        // guarde porque si abre en otro device no va a estar)

    }

    @Override
    public void onClick(View v) {

        if (v.getId() == R.id.button2) {

            //setear constante string chatwith para saber q chat mostrar en chat activity

            Intent chat = new Intent(this, ChatActivity.class);
            startActivity(chat);

        }
    }
}
