package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;
import android.widget.Toast;

import com.example.fernando.myapplication.Activities.ChatsHallActivity;
import com.example.fernando.myapplication.Common.Constants;

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
            Thread.sleep(20);

            if (Constants.user.chats.size() > Constants.currentChatsSize) {

                for (int chat = Constants.currentChatsSize;
                     chat < Constants.user.chats.size();
                     chat++) {

                    publishProgress("refresh", Constants.user.chats.get(chat).otherUser);
                }
                Constants.currentChatsSize = Constants.user.chats.size();
            }
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
        } else if (values[0].compareTo("refresh") == 0){
            Constants.chatsAdapter.add(values[1]);
            Constants.chatListView.setAdapter(Constants.chatsAdapter);
        }
    }
}
