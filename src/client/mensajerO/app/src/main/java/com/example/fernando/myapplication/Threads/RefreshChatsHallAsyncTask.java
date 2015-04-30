package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;

import com.example.fernando.myapplication.Activities.ChatsHallActivity;
import com.example.fernando.myapplication.Common.Constants;

/**
 * Created by fernando on 27/04/15.
 */
public class RefreshChatsHallAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {
    @Override
    protected String doInBackground(Pair<Context, String>... params) {
        int currentChatsSize = Constants.userChats.size();
        // sizeActual de la lista de chats
        while (!isCancelled()) {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            if (Constants.userChats.size() > currentChatsSize) {
                currentChatsSize = Constants.userChats.size();

                for (int chat = (Constants.userChats.size() - currentChatsSize);
                     chat < Constants.userChats.size();
                        chat++) {

                    Constants.chatsAdapter.add(Constants.userChats.get(chat).otherUser);
                }
                Constants.chatListView.setAdapter(Constants.chatsAdapter);
            }
        }

        return null;
    }
}
