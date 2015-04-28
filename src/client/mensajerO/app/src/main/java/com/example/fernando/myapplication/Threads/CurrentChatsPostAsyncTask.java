package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;

import com.example.fernando.myapplication.Common.Constants;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.util.EntityUtils;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by fernando on 27/04/15.
 */
public class CurrentChatsPostAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {
    @Override
    protected String doInBackground(Pair<Context, String>... params) {
        //        context = params[0].first;
        String name = params[0].second;

        String url = params[1].second;

        String type = params[2].second;

        HttpClient httpClient = new DefaultHttpClient();
        HttpPost httpPost = new HttpPost(url);

        try {
            // Add name data to request
            List<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>(1);
            nameValuePairs.add(new BasicNameValuePair("name", name));
            httpPost.setEntity(new UrlEncodedFormEntity(nameValuePairs));

            // Execute HTTP Post Request
            HttpResponse response = httpClient.execute(httpPost);
            if (response.getStatusLine().getStatusCode() == 200) {
                return EntityUtils.toString(response.getEntity());
            }
            return "Error: " + response.getStatusLine().getStatusCode() + " " + response.getStatusLine().getReasonPhrase();

//            // Execute HTTP GET Request
//            HttpResponse responseGET = httpClient.execute(httpGet);
//            if (responseGET.getStatusLine().getStatusCode() == 200) {
//                return EntityUtils.toString(responseGET.getEntity());
//            }
//            return "Error: " + responseGET.getStatusLine().getStatusCode() + " " + responseGET.getStatusLine().getReasonPhrase();

        } catch (ClientProtocolException e) {
            return e.getMessage();
        } catch (IOException e) {
            return e.getMessage();
        }
    }

    @Override
    protected void onPostExecute(String result) {
        // aca desempaqueto el package respuesta
//        try {

        JSONObject response = Constants.packager.unwrap(result);

        // sacar del response los chats y meterlos en Constants.userChats
        // si no viene nada meter un elemento asi sale del loop la activity

//        } catch (JSONException e) {
//            e.printStackTrace();
//        }

    }

}