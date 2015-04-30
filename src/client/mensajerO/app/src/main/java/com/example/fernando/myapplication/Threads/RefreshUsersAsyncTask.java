package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;

import com.example.fernando.myapplication.Activities.ChatsHallActivity;
import com.example.fernando.myapplication.Common.Constants;

/**
 * Created by fernando on 27/04/15.
 */
public class RefreshUsersAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {
    @Override
    protected String doInBackground(Pair<Context, String>... params) {
        int currentUsersSize = Constants.otherUsers.size();
        // sizeActual de la lista de chats
        while (!isCancelled()) {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            if (Constants.otherUsers.size() > currentUsersSize) {
                currentUsersSize = Constants.otherUsers.size();
                .drawCurrentUsers();
            }
            // O HACER ESTOO !!!!! PROBAR AMBOS Y VER EL MEJOR
            // si el sizeactual de la lista de chats es mayor que sizeActual
//               adapter.add("chatAgregado1");
            //               adapter.add("chatAgregado2"); ....
//               listview.setAdapter(adapter);
        }

        return null;
    }
}
