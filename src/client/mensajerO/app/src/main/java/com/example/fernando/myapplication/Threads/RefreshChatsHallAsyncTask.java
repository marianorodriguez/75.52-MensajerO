package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;

import com.example.fernando.myapplication.Activities.ChatsHallActivity;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Entities.Chat;
import com.example.fernando.myapplication.Entities.User;

/**
 * Created by fernando on 27/04/15.
 */
public class RefreshChatsHallAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {

    private Context context;
    @Override
    protected String doInBackground(Pair<Context, String>... params) {

        //Constants.currentChatsSize = Constants.user.chats.size();
        context = params[0].first;
        try {
            Thread.sleep(1000);

//            if (Constants.user.chats.size() > Constants.currentChatsSize) {
//
//                for (int chat = Constants.currentChatsSize;
//                     chat < Constants.user.chats.size();
//                     chat++) {
//
//                    publishProgress("refresh", Constants.user.chats.get(chat).otherUser);
//                }
//                Constants.currentChatsSize = Constants.user.chats.size();
//            }

//            refreshChatsData();
            publishProgress("refresh");

            publishProgress("run again", params[0].second,
                    params[1].second, params[2].second);

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    protected void onProgressUpdate(String... values) {
        super.onProgressUpdate(values);

        if (values[0].compareTo("run again") == 0) {
//            Toast.makeText(context, "new refresh", Toast.LENGTH_LONG).show();
            ChatsHallActivity.refreshChats = new RefreshChatsHallAsyncTask();
            ChatsHallActivity.refreshChats.execute(new Pair<>(context, values[1]),
                    new Pair<>(context, values[2]),
                    new Pair<>(context, values[3]));
            this.cancel(true);
        } else if (values[0].compareTo("refresh") == 0) {

            Constants.chatsAdapter.clear();

            for (int chat = 0; chat < Constants.user.chats.size(); chat++) {
                Chat chatToShow = Constants.user.chats.get(chat);

                Constants.chatsAdapter.add(chatToShow.otherUser);
//                        + "\n" +
//                        userToShow.status + " - "
//                        + userToShow.lastTimeConnected
//                        + " - " + userToShow.location);
//                Constants.usersListView.setAdapter(Constants.usersAdapter);
            }
            Constants.chatListView.setAdapter(Constants.chatsAdapter);
//
//            Constants.chatsAdapter.add(values[1]);
//            Constants.chatListView.setAdapter(Constants.chatsAdapter);
        }
    }
}
