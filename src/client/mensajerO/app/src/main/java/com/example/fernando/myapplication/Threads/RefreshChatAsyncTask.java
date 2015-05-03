package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;

import com.example.fernando.myapplication.Common.Chat;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Common.Message;

import java.util.ArrayList;

/**
 * Created by fernando on 27/04/15.
 */
public class RefreshChatAsyncTask extends AsyncTask<Pair<Context, Chat>, String, String> {

    private Chat chatToUpdate;

    @Override
    protected String doInBackground(Pair<Context, Chat>... params) {
        chatToUpdate = params[0].second;

        int messagesSize = chatToUpdate.messages.size();

        while (!isCancelled()) {
            if (chatToUpdate.messages.size() > messagesSize) {

                ArrayList<Message> newMessages = new ArrayList<>();
                for (int message = messagesSize;
                     message < chatToUpdate.messages.size();
                     message++) {
                    newMessages.add(chatToUpdate.messages.get(message));
                }
                messagesSize = chatToUpdate.messages.size();
                Constants.chatEditor.renderNewMessages(newMessages);
            }
        }

        return null;
    }
}
