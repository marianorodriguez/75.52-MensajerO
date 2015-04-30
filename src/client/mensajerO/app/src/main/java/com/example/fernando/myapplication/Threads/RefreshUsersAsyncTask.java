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

                for (int user = (Constants.otherUsers.size() - currentUsersSize);
                     user < Constants.otherUsers.size();
                     user++) {

                    Constants.usersAdapter.add(Constants.otherUsers.get(user).username);
                }
                Constants.usersListView.setAdapter(Constants.usersAdapter);

            }
        }

        return null;
    }
}
