package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;

import com.example.fernando.myapplication.Common.Constants;

/**
 * Created by fernando on 27/04/15.
 */
public class RefreshUsersAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {

    @Override
    protected String doInBackground(Pair<Context, String>... params) {

        int currentUsersSize = Constants.otherUsers.size();

        while (!isCancelled()) {
            try {
                Thread.sleep(1000);

            if (Constants.otherUsers.size() > currentUsersSize) {

                for (int user = currentUsersSize;
                     user < Constants.otherUsers.size();
                     user++) {

                    publishProgress(Constants.otherUsers.get(user).username);
                }
                currentUsersSize = Constants.otherUsers.size();
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

        Constants.usersAdapter.add(values[0]);
        Constants.usersListView.setAdapter(Constants.usersAdapter);
    }

}
