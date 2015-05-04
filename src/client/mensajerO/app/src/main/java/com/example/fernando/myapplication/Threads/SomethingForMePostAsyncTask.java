package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.os.SystemClock;
import android.util.Pair;
import android.widget.Toast;

import com.example.fernando.myapplication.Activities.ChatsHallActivity;
import com.example.fernando.myapplication.Common.Chat;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Common.Message;
import com.example.fernando.myapplication.Mocks.Mocks;

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
public class SomethingForMePostAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {
    boolean serverError = false;
    private Context context;
    @Override
    protected String doInBackground(Pair<Context, String>... params) {

        try {
            Thread.sleep(200);
            context = params[0].first;

            if ( Constants.server != null ) {
                String response = Constants.server.somethingForMe(params[0].second);

                allocateMessages(response);

                publishProgress("run again", params[0].second,
                        params[1].second, params[2].second);

                return "";

            } else {
                HttpResponse response = doRequest(params);

                if (response.getStatusLine().getStatusCode() == 200) {

                    allocateMessages(EntityUtils.toString(response.getEntity()));

                    publishProgress("run again", params[0].second,
                            params[1].second, params[2].second);

                    return EntityUtils.toString(response.getEntity());

                } else {
                    publishProgress("serverError");

                    publishProgress("run again", params[0].second,
                            params[1].second, params[2].second);

                    //Toast.makeText(params[0].first, "Could't connect with server", Toast.LENGTH_LONG).show();
                }
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

    @Override
    protected void onProgressUpdate(String... values) {
        super.onProgressUpdate(values);

        if (values[0].compareTo("serverError") == 0)
            Toast.makeText(context, "Could't connect with server", Toast.LENGTH_LONG).show();
        else {
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
            Toast.makeText(context, "Could't connect with server", Toast.LENGTH_LONG).show();

    }

    private void allocateMessages(String response) {
        JSONArray newMessages = Constants.packager.unwrap(response, "messages");
        boolean createNewChat;

        if (newMessages == null) return;
        for (int message = 0; message < newMessages.length(); message++) {
            createNewChat = true;
            try {
                Message newMessage = Message.toMessage((JSONObject) newMessages.get(message));

                for (int chat = 0; chat < Constants.user.chats.size(); chat++) {
                    if (Constants.user.chats.get(chat).otherUser.compareTo(newMessage.emisor) == 0) {
                        Constants.user.chats.get(chat).messages.add(newMessage);
                        chat = Constants.user.chats.size();
                        createNewChat = false;
                    }
                }

                if (createNewChat) {
                    Chat newChat = new Chat(newMessage.emisor);
                    newChat.messages.add(newMessage);
                    Constants.user.chats.add(newChat);
                }

            } catch (JSONException e) {
                e.printStackTrace();
            }
        }

    }
}