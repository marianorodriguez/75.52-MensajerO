package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;

/**
 * Created by fernando on 27/04/15.
 */
public class GetUsersAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {

    @Override
    protected String doInBackground(Pair<Context, String>... params) {

        while (!isCancelled()) {

            // hacer el post
            // si el size del vector de usuarios qe me llega es mayor del qe tengo
                // agrego los ultimos users a mi lista

            // si hay error no mostrar nada porque va a mostrar somethingForMe
        }

        return null;
    }
}
