package com.fiuba.tallerii.mensajer0.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;
import android.widget.Toast;

import com.fiuba.tallerii.mensajer0.Activities.ChatsHallActivity;
import com.fiuba.tallerii.mensajer0.Common.Constants;
import com.fiuba.tallerii.mensajer0.Entities.User;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpGet;
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
            Thread.sleep(Constants.GetUsersPostAsyncTaskFrec);
            context = params[0].first;

            if (Constants.GetUsersPostAsyncTaskFinish) return null;

            if ( Constants.server != null ) {
                String response = Constants.server.users(params[0].second);

                resizeUsers(response);

                publishProgress("run again", params[0].second,
                        params[1].second, params[2].second);

                return "";

            } else {
                HttpResponse response = doRequest(params);

                if ( response!= null && response.getStatusLine().getStatusCode() == 200) {

                    resizeUsers(EntityUtils.toString(response.getEntity()));

                    publishProgress("run again", params[0].second,
                            params[1].second, params[2].second);

                    return "";

                }

                return null;
            }

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
            Toast.makeText(context, "Couldn't connect with server", Toast.LENGTH_LONG).show();
//        else if (values[0].compareTo("updateUsers") == 0) {
//
//            Constants.usersAdapter.clear();
//
//            for (int user = 0; user < Constants.otherUsers.size(); user++) {
//                Constants.usersAdapter.add(Constants.otherUsers.get(user).username);
//                Constants.usersListView.setAdapter(Constants.usersAdapter);
//            }

        else {
//            Toast.makeText(context, "new user thread", Toast.LENGTH_LONG).show();
            ChatsHallActivity.getUsersPost = new GetUsersPostAsyncTask();
            ChatsHallActivity.getUsersPost.execute(new Pair<>(context, values[1]),
                    new Pair<>(context, values[2]),
                    new Pair<>(context, values[3]));
            this.cancel(true);
        }
    }

    private HttpResponse doRequest(Pair<Context, String>... params) {
        String package_ = params[0].second;
        String url = params[1].second;
        String type = params[2].second;

        try {

            HttpClient httpClient = new DefaultHttpClient();
            HttpResponse response;

            if (type.compareTo("post") == 0) {

                HttpPost httpPost = new HttpPost(url);

                // Add name data to request
                List<NameValuePair> nameValuePairs = new ArrayList<>(1);
                nameValuePairs.add(new BasicNameValuePair("package", package_));
                httpPost.setEntity(new UrlEncodedFormEntity(nameValuePairs));

                // Execute HTTP Post Request
                response = httpClient.execute(httpPost);

                return response;

            } else if (type.compareTo("get") == 0) {

                url = url.concat("?" + package_);

                response = httpClient.execute(new HttpGet(url));

                return response;

            }
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

        ArrayList<User> otherUsers = new ArrayList<>();

        for (int user = 0; user < users.length(); user++) {
            try {

                JSONObject objectUser = new JSONObject(users.get(user).toString());
                User newUser = User.toUser(objectUser);

                if (newUser.username.compareTo(Constants.user.username) != 0 &&
                        newUser.status.compareTo("offline") != 0) {
                    otherUsers.add(newUser);
                }

            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        Constants.otherUsers = otherUsers;
    }

}