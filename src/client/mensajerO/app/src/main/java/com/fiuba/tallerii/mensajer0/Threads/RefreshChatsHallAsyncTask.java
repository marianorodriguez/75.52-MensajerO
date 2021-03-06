package com.fiuba.tallerii.mensajer0.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;
import android.widget.Toast;

import com.fiuba.tallerii.mensajer0.Activities.ChatsHallActivity;
import com.fiuba.tallerii.mensajer0.Common.Constants;
import com.fiuba.tallerii.mensajer0.Entities.Chat;

/**
 * Clase usada para hacer la conexion con el servidor pidiendo una actualizacion de los distintos chats con los distintos usuarios. 
 */
public class RefreshChatsHallAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {

    private Context context;

    @Override
    protected String doInBackground(Pair<Context, String>... params) {

        context = params[0].first;
        try {
            Thread.sleep(1000);
            if (Constants.RefreshChatsHallAsyncTaskFinish) return null;

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
            }
            Constants.chatListView.setAdapter(Constants.chatsAdapter);

        }
    }
}
