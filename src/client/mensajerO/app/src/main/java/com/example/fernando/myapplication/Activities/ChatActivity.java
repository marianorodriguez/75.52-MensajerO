package com.example.fernando.myapplication.Activities;

import android.content.Context;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Pair;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import com.example.fernando.myapplication.Common.Chat;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Common.Message;
import com.example.fernando.myapplication.Threads.RefreshChatAsyncTask;
import com.example.fernando.myapplication.R;
import com.example.fernando.myapplication.Threads.SendMessagePostAsyncTask;

/**
 * Created by fernando on 10/04/15.
 */
public class ChatActivity extends ActionBarActivity implements View.OnClickListener {

    RefreshChatAsyncTask refreshChat;
    SendMessagePostAsyncTask sendMessage;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.chat);

        setTitle(getResources().getString(R.string.chat).concat(Constants.chatWith));

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

            EditText edTxt = (EditText) findViewById(R.id.editText);
            String message = edTxt.getText().toString();

            String package_ = Constants.packager.wrap("logIn", Constants.user, Constants.chatWith, message);

            sendMessage.execute(new Pair<Context, String>(this, package_),
                    new Pair<Context, String>(this, Constants.sendMessageUrl),
                    new Pair<Context, String>(this, "post"));

            while (Constants.sendMessageOk.compareTo("") == 0) {}

            if (Constants.sendMessageOk.contains("Error")) {}

            if (Constants.sendMessageOk.compareTo("true") == 0) {
                edTxt.setText("");
                Message newMessage = new Message(
                        Constants.user.username,
                        message,
                        Constants.messageDate.toString(),
                        Constants.messageTime.toString());
                Constants.chatEditor.renderNewMessage(newMessage);
            }
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        refreshChat.cancel(true);
    }
}
