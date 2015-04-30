package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.os.SystemClock;
import android.util.Pair;
import android.widget.Toast;

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

        while (!isCancelled()) {
            try {

                Thread.sleep(1000);
                context = params[0].first;
                String packageToSend = params[0].second;
                String url = params[1].second;
                String type = params[2].second;

                HttpClient httpClient = new DefaultHttpClient();
                HttpPost httpPost = new HttpPost(url);

                // Add name data to request
                List<NameValuePair> nameValuePairs = new ArrayList<>(1);
                nameValuePairs.add(new BasicNameValuePair("name", packageToSend));
                httpPost.setEntity(new UrlEncodedFormEntity(nameValuePairs));

                //Execute HTTP Post Request
                HttpResponse response = httpClient.execute(httpPost);
                if (response.getStatusLine().getStatusCode() == 200) {
                    allocateMessages(EntityUtils.toString(response.getEntity()));

                }else {

                    Toast.makeText(params[0].first, "Could't connect with server", Toast.LENGTH_LONG).show();
                }
    //
    ////            // Execute HTTP GET Request
    ////            HttpResponse responseGET = httpClient.execute(httpGet);
    ////            if (responseGET.getStatusLine().getStatusCode() == 200) {
    ////                return EntityUtils.toString(responseGET.getEntity());
    ////            }
    ////            return "Error: " + responseGET.getStatusLine().getStatusCode() + " " + responseGET.getStatusLine().getReasonPhrase();
    //
            } catch (ClientProtocolException e) {
                serverError = true;
                return e.getMessage();
            } catch (IOException e) {
                serverError = true;
                return e.getMessage();
            } catch (InterruptedException e) {
                serverError = true;
                e.printStackTrace();
                return "";
            }
        }
        return null;
    }

    @Override
    protected void onPostExecute(String s) {
        super.onPostExecute(s);

        if (serverError)
            Toast.makeText(context, "Could't connect with server", Toast.LENGTH_LONG).show();

    }

    private void allocateMessages(String response) {
        JSONArray newMessages = Constants.packager.unwrap(response, 0);
        boolean createNewChat;
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
                }

            } catch (JSONException e) {
                e.printStackTrace();
            }
        }

    }
}