package com.fiuba.tallerii.mensajer0.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Toast;

import com.fiuba.tallerii.mensajer0.Activities.ChatsHallActivity;
import com.fiuba.tallerii.mensajer0.Entities.Chat;
import com.fiuba.tallerii.mensajer0.Common.Constants;
import com.fiuba.tallerii.mensajer0.Entities.Message;
import com.example.fernando.mensajerO.R;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.params.BasicHttpParams;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;
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
public class SomethingForMePostAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {
    boolean serverError = false;
    private Context context;

    @Override
    protected String doInBackground(Pair<Context, String>... params) {

        try {
            Thread.sleep(50);
            context = params[0].first;

            if ( Constants.server != null ) {
                String response = Constants.server.somethingForMe(params[0].second);

                allocateMessages(response);

                publishProgress("run again", params[0].second,
                        params[1].second, params[2].second);

                return "";

            } else {
                    HttpResponse response = doRequest(params);

                if (response != null && response.getStatusLine().getStatusCode() == 200) {

                    allocateMessages(EntityUtils.toString(response.getEntity()));

                    publishProgress("run again", params[0].second,
                            params[1].second, params[2].second);

                    return "";

                } else {
                    publishProgress("serverError");
                    return null;
                }
                //return "Error: " + response.getStatusLine().getStatusCode() + " " + response.getStatusLine().getReasonPhrase();
            }

        } catch (InterruptedException e) {
            serverError = true;
            e.printStackTrace();
            return "";
        } catch (IOException e) {
            serverError = true;
            e.printStackTrace();
            return "";
        }

    }

    private HttpResponse doRequest(Pair<Context, String>... params) {
        String package_ = params[0].second;
        String url = params[1].second;
        String type = params[2].second;

        try {

            HttpParams httpParameters = new BasicHttpParams();
// Set the timeout in milliseconds until a connection is established.
// The default value is zero, that means the timeout is not used.
            int timeoutConnection = 3000;
            HttpConnectionParams.setConnectionTimeout(httpParameters, timeoutConnection);
// Set the default socket timeout (SO_TIMEOUT)
// in milliseconds which is the timeout for waiting for data.
            int timeoutSocket = 5000;
            HttpConnectionParams.setSoTimeout(httpParameters, timeoutSocket);

            HttpClient httpClient = new DefaultHttpClient(httpParameters);
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

    @Override
    protected void onProgressUpdate(String... values) {
        super.onProgressUpdate(values);

        if (values[0].compareTo("serverError") == 0) {
            Toast.makeText(context, "Couldn't connect with server. Try again later. Excuse us.", Toast.LENGTH_LONG).show();

            Constants.RefreshChatsHallAsyncTaskFinish = true;
            Constants.GetUsersPostAsyncTaskFinish = true;
            Constants.SomethingForMePostAsyncTaskFinish = true;
            Constants.RefreshUsersAsyncTaskFinish = true;

            LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            View logoutButton = inflater.inflate(R.layout.logout, null);
//            logoutButton.findViewById(R.id.logOutButton).performClick();
            logoutButton.findViewById(R.id.logOutButton).callOnClick();

        } else {
//            Toast.makeText(context, "new hilo", Toast.LENGTH_LONG).show();
            ChatsHallActivity.somethingForMePost = new SomethingForMePostAsyncTask();
            ChatsHallActivity.somethingForMePost.execute(new Pair<>(context, values[1]),
                    new Pair<>(context, values[2]),
                    new Pair<>(context, values[3]));
//            Toast.makeText(context, "new hilo ds", Toast.LENGTH_LONG).show();
            this.cancel(true);
        }
    }

    @Override
    protected void onPostExecute(String s) {
        super.onPostExecute(s);

        if (serverError)
            Toast.makeText(context, "Couldn't connect with server", Toast.LENGTH_LONG).show();

    }

    private void allocateMessages(String response) {
        JSONArray newMessages = Constants.packager.unwrap(response, "messages");
        boolean createNewChat;

        if (newMessages == null) return;
        for (int message = 0; message < newMessages.length(); message++) {
            createNewChat = true;
            try {

                JSONObject object = new JSONObject(newMessages.get(message).toString());
//                    JSONObject jsonObject = new JSONObject(username);

                Message newMessage = Message.toMessage(object);
//
//                User newUser = User.toUser(object);
//
//                Message newMessage = Message.toMessage((JSONObject) newMessages.get(message));

                for (int chat = 0; chat < Constants.user.chats.size(); chat++) {
                    if (Constants.user.chats.get(chat).otherUser.compareTo(newMessage.msg_fromID) == 0) {
                        Constants.user.chats.get(chat).messages.add(newMessage);
                        chat = Constants.user.chats.size();
                        createNewChat = false;
                    }
                }

                if (createNewChat) {
                    Chat newChat = new Chat(newMessage.msg_fromID);
                    newChat.messages.add(newMessage);
                    Constants.user.chats.add(newChat);
                }

            } catch (JSONException e) {
                e.printStackTrace();
            }
        }

    }
}