package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;
import android.widget.Toast;

import com.example.fernando.myapplication.Activities.ChatsHallActivity;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Entities.User;

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
            Thread.sleep(200);
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

                    return "";

                }

                return "Error: " + response.getStatusLine().getStatusCode() + " " + response.getStatusLine().getReasonPhrase();
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
            Toast.makeText(context, "Could't connect with server", Toast.LENGTH_LONG).show();
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

//        Constants.otherUsers.clear();
//        for (int userr = 0; userr < users.length(); userr++) {
//            try {
////                    Constants.otherUsers.add(new User(users.getJSONObject(user)));
////                    users.optJSONObject(user);
//                JSONObject object = new JSONObject(users.get(userr).toString());
////                    JSONObject jsonObject = new JSONObject(username);
//
//                User newUser = User.toUser(object);
//                if (newUser.username.compareTo(Constants.user.username) != 0) {
//                    Constants.otherUsers.add(newUser);
//                }
//            } catch (JSONException e) {
//                e.printStackTrace();
//            }
//        }
//        return;

        //sacar

        //c

        //sacar
        ArrayList<User> otherUsers = new ArrayList<>();
//        Constants.otherUsers.clear();
        for (int user = 0; user < users.length(); user++) {
            try {

                JSONObject objectUser = new JSONObject(users.get(user).toString());
                User newUser = User.toUser(objectUser);

                if (newUser.username.compareTo(Constants.user.username) != 0 &&
                        newUser.status.compareTo("offline") != 0) {
                    otherUsers.add(newUser);
                }

            } catch (JSONException e) {
                e.printStackTrace();
            }
        }

        Constants.otherUsers = otherUsers;

//        publishProgress ("updateUsers");

//        sacar este usuario y sacar los qe tiene estado de conexion no conectdo (antes de agregar a la lista);
//
//        if ((users.length()-1) > Constants.otherUsers.size()) {
//            // se agrego uno o mas usuarios nuevos a mensajerO
//
//            for (int user = 0; user < users.length(); user++) {
//                try {
//
//                    JSONObject objectUser = new JSONObject(users.get(user).toString());
//                    User newUser = User.toUser(objectUser);
//
//                    for (int otherUser = 0; other)
//
//                    if (newUser.username.compareTo(Constants.user.username) != 0) {
//                        Constants.otherUsers.add(newUser);
//                    }
//                } catch (JSONException e) {
//                    e.printStackTrace();
//                }
//            }
//        }
//
//        refreshUsersData(users);

    }

    private void refreshUsersData(JSONArray users) {

    }
}