package com.example.fernando.myapplication.Activities;

import android.content.Context;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Pair;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;

import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Common.ServletPostAsyncTask;
import com.example.fernando.myapplication.R;

/**
 * Created by fernando on 10/04/15.
 */
public class ChatActivity extends ActionBarActivity {

    ServletPostAsyncTask refreshChat;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.chat);

        // dibujar los mensajes del chat actual con chatwith user

        refreshChat = new ServletPostAsyncTask();
        refreshChat.execute(new Pair<Context, String>(this, ""),
                new Pair<Context, String>(this, ""),
                new Pair<Context, String>(this, ""));
        // tirar hilo que se fije si de en la lista de chats hay cambios con este user y actualice la vista
    }

}
