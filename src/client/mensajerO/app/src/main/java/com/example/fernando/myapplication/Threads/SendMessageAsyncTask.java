package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;

/**
 * Created by fernando on 27/04/15.
 */
public class SendMessageAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {
    @Override
    protected String doInBackground(Pair<Context, String>... params) {
        //le pasan un message como parametro y se lo manda al server

        return null;
    }
}
