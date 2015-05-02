package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;

import com.example.fernando.myapplication.Common.Constants;

/**
 * Created by fernando on 27/04/15.
 */
public class RefreshChatsHallAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {
    @Override
    protected String doInBackground(Pair<Context, String>... params) {

        int currentChatsSize = Constants.user.chats.size();

        while (!isCancelled()) {
            try {
                Thread.sleep(1000);

                if (Constants.user.chats.size() > currentChatsSize) {

                    for (int chat = currentChatsSize;
                         chat < Constants.user.chats.size();
                         chat++) {

                        publishProgress(Constants.user.chats.get(chat).otherUser);
                    }
                    currentChatsSize = Constants.user.chats.size();
                }

            } catch (InterruptedException e) {
                e.printStackTrace();
                return null;
            }
        }
        return null;
    }

    @Override
    protected void onProgressUpdate(String... values) {
        super.onProgressUpdate(values);

        Constants.chatsAdapter.add(values[0]);
        Constants.chatListView.setAdapter(Constants.chatsAdapter);
    }
}
