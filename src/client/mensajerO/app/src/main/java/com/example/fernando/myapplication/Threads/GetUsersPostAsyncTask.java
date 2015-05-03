package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;
import android.widget.Toast;

import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Common.User;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.util.EntityUtils;
import org.json.JSONArray;
import org.json.JSONException;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by fernando on 27/04/15.
 */
public class GetUsersPostAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {

    @Override
    protected String doInBackground(Pair<Context, String>... params) {

        while (!isCancelled()) {
            try {

                Thread.sleep(1500);

                String packageToSend = params[0].second;
                String url = params[1].second;
                String type = params[2].second;

                HttpClient httpClient = new DefaultHttpClient();
                HttpPost httpPost = new HttpPost(url);

                // Add name data to request
                List<NameValuePair> nameValuePairs = new ArrayList<>(1);
                nameValuePairs.add(new BasicNameValuePair("package", packageToSend));
                httpPost.setEntity(new UrlEncodedFormEntity(nameValuePairs));

                //Execute HTTP Post Request
                HttpResponse response = httpClient.execute(httpPost);
                if (response.getStatusLine().getStatusCode() == 200) {
                    resizeUsers(EntityUtils.toString(response.getEntity()));

                }
//                Toast.makeText(params[0].first, "Could't connect with server", Toast.LENGTH_LONG).show();
                //
                ////            // Execute HTTP GET Request
                ////            HttpResponse responseGET = httpClient.execute(httpGet);
                ////            if (responseGET.getStatusLine().getStatusCode() == 200) {
                ////                return EntityUtils.toString(responseGET.getEntity());
                ////            }
                ////            return "Error: " + responseGET.getStatusLine().getStatusCode() + " " + responseGET.getStatusLine().getReasonPhrase();
                //
            } catch (ClientProtocolException e) {
                return e.getMessage();
            } catch (IOException e) {
                return e.getMessage();
            } catch (InterruptedException e) {
                e.printStackTrace();
                return null;
            }
        }
        return null;
    }

    private void resizeUsers(String response) {
        JSONArray users = Constants.packager.unwrap(response, 0);

        if (users.length() > Constants.otherUsers.size()) {
            for (int user = (users.length()-Constants.otherUsers.size());
                    user < users.length();
                    user++ ) {
                try {
                    Constants.otherUsers.add(User.toUser((org.json.JSONObject) users.get(user)));
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}

// hacer el post
// si el size del vector de usuarios qe me llega es mayor del qe tengo
// agrego los ultimos users a mi lista

// si hay error no mostrar nada porque va a mostrar somethingForMe