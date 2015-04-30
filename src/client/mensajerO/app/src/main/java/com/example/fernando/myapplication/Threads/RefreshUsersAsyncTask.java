package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;

/**
 * Created by fernando on 27/04/15.
 */
public class RefreshUsersAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {
    @Override
    protected String doInBackground(Pair<Context, String>... params) {
        // sizeActual de la lista de userrs
        while (!isCancelled()) {
            // si el sizeactual de la lista de users es mayor que sizeActual
//               adapter.add("userAgregado1");
            //               adapter.add("userAgregado2"); ....
//               listview.setAdapter(adapter);

        }

        return null;
    }
}
