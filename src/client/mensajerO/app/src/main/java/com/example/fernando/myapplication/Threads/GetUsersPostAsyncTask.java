package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;
import android.widget.Toast;

import com.example.fernando.myapplication.Activities.ChatsHallActivity;
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
import org.json.JSONObject;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by fernando on 27/04/15.
 */
public class GetUsersPostAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {

    private Context context;

    @Override
    protected String doInBackground(Pair<Context, String>... params) {

        try {
            Thread.sleep(2000);
            context = params[0].first;

            if ( Constants.server != null ) {
                String response = Constants.server.users(params[0].second);

                resizeUsers(response);

                publishProgress("run again", params[0].second,
                        params[1].second, params[2].second);

                return "";

            } else {
                HttpResponse response = doRequest(params);
                if (response.getStatusLine().getStatusCode() == 200) {

                    resizeUsers(EntityUtils.toString(response.getEntity()));

                    publishProgress("run again", params[0].second,
                            params[1].second, params[2].second);

                    return EntityUtils.toString(response.getEntity());

                }

                publishProgress("run again", params[0].second,
                        params[1].second, params[2].second);

                return "Error: " + response.getStatusLine().getStatusCode() + " " + response.getStatusLine().getReasonPhrase();
            }
            //
            ////            // Execute HTTP GET Request
            ////            HttpResponse responseGET = httpClient.execute(httpGet);
            ////            if (responseGET.getStatusLine().getStatusCode() == 200) {
            ////                return EntityUtils.toString(responseGET.getEntity());
            ////            }
            ////            return "Error: " + responseGET.getStatusLine().getStatusCode() + " " + responseGET.getStatusLine().getReasonPhrase();
            //

        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    protected void onProgressUpdate(String... values) {
        super.onProgressUpdate(values);

        if (values[0].compareTo("serverError") == 0)
            Toast.makeText(context, "Could't connect with server", Toast.LENGTH_LONG).show();
        else {
            Toast.makeText(context, "new user thread", Toast.LENGTH_LONG).show();
            ChatsHallActivity.usersPost = new GetUsersPostAsyncTask();
            ChatsHallActivity.usersPost.execute(new Pair<>(context, values[1]),
                    new Pair<>(context, values[2]),
                    new Pair<>(context, values[3]));
            this.cancel(true);
        }
    }

    private HttpResponse doRequest(Pair<Context, String>... params) {
        try {
            String package_ = params[0].second;
            String url = params[1].second;
            String type = params[2].second;

            HttpClient httpClient = new DefaultHttpClient();
            HttpPost httpPost = new HttpPost(url);

            // Add name data to request
            List<NameValuePair> nameValuePairs = new ArrayList<>(1);
            nameValuePairs.add(new BasicNameValuePair("package", package_));
            httpPost.setEntity(new UrlEncodedFormEntity(nameValuePairs));

            // Execute HTTP Post Request
            HttpResponse response = httpClient.execute(httpPost);

            return response;
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        } catch (ClientProtocolException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    private void resizeUsers(String response) {
        JSONArray users = Constants.packager.unwrap(response, "users");

        if (users == null) return;
        if (users.length() > Constants.otherUsers.size()) {
            for (int user = Constants.otherUsers.size();
                    user < users.length();
                    user++ ) {
                try {
                    Constants.otherUsers.add(new User(users.getString(user)));
//                    Constants.otherUsers.add(User.toUser((org.json.JSONObject) users.get(user)));
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}