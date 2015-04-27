package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;

/**
 * Created by fernando on 27/04/15.
 */
public class SomethingForMeAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {

    @Override
    protected String doInBackground(Pair<Context, String>... params) {

        while (!isCancelled()) {
            // cada x tiempo

            // hacer el post
            // desempaquetar el response
            // si hay mensajes nuevos:
                // recorrer cada mensage, ver el emisor, ver si ya hay chat con ese emisor
                    // si hay agregar mensajes al chat
                    //sino crear nuevo chat, agregar esos mensajes y agregar al user


            // si hay error en el post mostrar toast(cant connect with server)

        }


        return null;
    }
}