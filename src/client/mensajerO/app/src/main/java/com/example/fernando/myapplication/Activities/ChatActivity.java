package com.example.fernando.myapplication.Activities;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Pair;
import android.view.View;
import android.widget.TextView;

import com.example.fernando.myapplication.Common.Chat;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Threads.RefreshChatAsyncTask;
import com.example.fernando.myapplication.R;
import com.example.fernando.myapplication.Threads.SendMessageAsyncTask;

/**
 * Created by fernando on 10/04/15.
 */
public class ChatActivity extends ActionBarActivity implements View.OnClickListener {

    RefreshChatAsyncTask refreshChat;
    SendMessageAsyncTask sendMessage;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.chat);

        TextView chat = (TextView) findViewById(R.id.chat);

        // SETEAR EL CHAT CORRESPONDIENTE A CHATEDITOR ANTES DE PASAR A ESTA ACTIVITY
        Constants.chatEditor.renderChat(chat);
        // dibujar los mensajes del chat actual con chatwith user


        refreshChat = new RefreshChatAsyncTask();
        refreshChat.execute(new Pair<Context, Chat>(this, Constants.chatEditor.getChat()));
        // tirar hilo que se fije si de en la lista de chats hay cambios con este user y actualice la vista
    }

    @Override
    public void onClick(View v) {

        if (v.getId() == R.id.sendButton) {

            // hacer el post con el mensagge en edit text
            // borrar el edittext
            // crear el nuevo mensaje y apendearlo al textview

        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        refreshChat.cancel(true);
    }
}
