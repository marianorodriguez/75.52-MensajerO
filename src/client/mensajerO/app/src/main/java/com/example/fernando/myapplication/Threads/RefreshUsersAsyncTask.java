package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;

import com.example.fernando.myapplication.Activities.UsersActivity;
import com.example.fernando.myapplication.Common.Constants;

/**
 * Created by fernando on 27/04/15.
 */
public class RefreshUsersAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {

    private Context context;

    @Override
    protected String doInBackground(Pair<Context, String>... params) {

//        Constants.currentUsersSize = Constants.otherUsers.size();
        context = params[0].first;
            try {
                Thread.sleep(200);

                if (Constants.otherUsers.size() > Constants.currentUsersSize) {

                    for (int user = Constants.currentUsersSize;
                         user < Constants.otherUsers.size();
                         user++) {

                        publishProgress(Constants.otherUsers.get(user).username);
                    }
                    Constants.currentUsersSize = Constants.otherUsers.size();
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
//            Toast.makeText(context, "new refresh users", Toast.LENGTH_LONG).show();
            UsersActivity.refreshUsers = new RefreshUsersAsyncTask();
            UsersActivity.refreshUsers.execute(new Pair<>(context, values[1]),
                    new Pair<>(context, values[2]),
                    new Pair<>(context, values[3]));
            this.cancel(true);
        } else {
            Constants.usersAdapter.add(values[0]);
            Constants.usersListView.setAdapter(Constants.usersAdapter);
        }
    }

}
