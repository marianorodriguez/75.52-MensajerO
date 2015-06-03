package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;

import com.example.fernando.myapplication.Entities.Chat;
import com.example.fernando.myapplication.Common.Constants;

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
public class CurrentChatsPostAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {
    @Override
    protected String doInBackground(Pair<Context, String>... params) {
        //        context = params[0].first;
        if ( Constants.server != null ) {
            String response = Constants.server.currentChats(params[0].second);

            try {

                JSONObject resp = Constants.packager.unwrap(response);

                JSONArray chats = new JSONArray(resp.getString("chats"));

                for (int chat = 0; chat < chats.length(); chat++) {
                    Constants.user.chats.add(Chat.toChat(chats.getJSONObject(chat)));
                }

                Constants.currentChatsOk = resp.getString("chats");

                return "";

            } catch (JSONException e) {
                e.printStackTrace();
            }
            return null;
        } else {
            HttpResponse response = doRequest(params);

            if (response.getStatusLine().getStatusCode() == 200) {
                try {

                    JSONObject respons = Constants.packager.unwrap(EntityUtils.toString(response.getEntity()));

                    JSONArray chats = new JSONArray(respons.getString("chats"));

                    for (int chat = 0; chat < chats.length(); chat++) {
                        Constants.user.chats.add(Chat.toChat(chats.getJSONObject(chat)));
                    }

                    Constants.currentChatsOk = respons.getString("chats");

                    return "";

                } catch (JSONException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return "Error: " + response.getStatusLine().getStatusCode() + " " + response.getStatusLine().getReasonPhrase();
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

        }catch(UnsupportedEncodingException e){
            e.printStackTrace();
        }catch(ClientProtocolException e){
            e.printStackTrace();
        }catch(IOException e){
            e.printStackTrace();
        }
        return null;

    }
}