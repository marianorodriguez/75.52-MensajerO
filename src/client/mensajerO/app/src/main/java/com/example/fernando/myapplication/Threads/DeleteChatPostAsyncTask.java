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
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.util.EntityUtils;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by fernando on 31/05/15.
 */
public class DeleteChatPostAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {
    @Override
    protected String doInBackground(Pair<Context, String>... params) {

        if ( Constants.server != null ) {
            String response = Constants.server.deleteChat(params[0].second);

            try {

                JSONObject resp = Constants.packager.unwrap(response);

                Constants.deleteOk = resp.getString("ok");

                return "";

            } catch (JSONException e) {
                e.printStackTrace();
            }
            return null;

        } else {

            HttpResponse response = doRequest(params);

            if (response.getStatusLine().getStatusCode() == 200) {
                try {

                    JSONObject respons = Constants.packager.unwrap(
                            EntityUtils.toString(response.getEntity()));

                    Constants.deleteOk = respons.getString("ok");

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

                url.concat("?" + package_);

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
