package com.example.fernando.myapplication.Activities;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Pair;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Common.ServletPostAsyncTask;
import com.example.fernando.myapplication.Common.User;
import com.example.fernando.myapplication.R;

import java.util.logging.Handler;

/**
 * Created by fernando on 10/04/15.
 */
public class ChatsHallActivity extends ActionBarActivity implements View.OnClickListener {

    ServletPostAsyncTask somethingForMePost;
    ServletPostAsyncTask usersPost;
    ServletPostAsyncTask refreshChats;
    public String something;
    String package_;

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

            Button button2 = (Button) findViewById(R.id.button2);
            button2.setOnClickListener(this);

            somethingForMePost = new ServletPostAsyncTask();
            something = "";
            refreshChats = new ServletPostAsyncTask();
            usersPost = new ServletPostAsyncTask();

//            dibujar los chats que vienen de login

            String username = Constants.mSharedPreferences.getString(Constants.PREF_NAME, "");
            String password = Constants.mSharedPreferences.getString(Constants.PREF_PASS, "");
            Toast.makeText(getApplicationContext(), "Welcome, " + username + "!", Toast.LENGTH_LONG).show();

            User currentUser = new User(username, password);

            package_ = Constants.packager.doPackage("logIn", currentUser);

            somethingForMePost.execute(new Pair<Context, String>(this, package_),
                    new Pair<Context, String>(this, Constants.somethingForMeUrl),
                    new Pair<Context, String>(this, "post"));

            while (something.compareTo("") == 0) {}

            if (something.contains("Error")) {
                // tirar toast (no se puede conectar con el server)
            } else {
                // si llega algo tirar pop up, y actualizar lista de chats (o hacerlo directo en el hilo!!!)
                something = "";
            }

            usersPost.execute(new Pair<Context, String>(this, package_),
                    new Pair<Context, String>(this, Constants.usersUrl),
                    new Pair<Context, String>(this, "post"));
            // tirar un hilo que llame a users, que tire todos los usuarios del sistema y cargarlos en constants.users
            // loopea, se hace constantemente. el server manda todos los users

            refreshChats.execute(new Pair<Context, String>(this, ""),
                    new Pair<Context, String>(this, ""),
                    new Pair<Context, String>(this, ""));
            // hilo que ve si hay chats nuevos en la lista de chats y si los hay
            // o si hay mensajes nuevo los muestre y los ordene

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
    protected void onDestroy() {
        super.onDestroy();

        new ServletPostAsyncTask().execute(new Pair<Context, String>(this, package_),
                new Pair<Context, String>(this, Constants.currentChatsUrl),
                new Pair<Context, String>(this, "post"));

        // getResponse
        // GUARDAR CHATS sharedPreferences !

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
