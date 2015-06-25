package com.fiuba.tallerii.mensajer0.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;

import com.fiuba.tallerii.mensajer0.Common.Constants;

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
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by fernando on 28/04/15.
 */
public class SignUpPostAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {

    @Override
    protected String doInBackground(Pair<Context, String>... params) {
        if ( Constants.server != null ) {
            String response = Constants.server.signUp(params[0].second);

            try {

                JSONObject respons = Constants.packager.unwrap(response);

                Constants.signUpOk = respons.getString("ok");
                if(Constants.signUpOk.compareTo("true")==0) {
                    Constants.signUpLocation = respons.getString("location");
                }

                return "";

            } catch (JSONException e) {
                e.printStackTrace();
            }
            return null;
        } else {
            HttpResponse response = doRequest(params);

            if (response != null && response.getStatusLine().getStatusCode() == 200) {
                try {

                    JSONObject respons = Constants.packager.unwrap(EntityUtils.toString(response.getEntity()));

                    Constants.signUpOk = respons.getString("ok");
                    if(Constants.signUpOk.compareTo("true")==0) {
                        Constants.signUpLocation = respons.getString("location");
                    }

                    return "";

                } catch (JSONException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            Constants.signUpOk = "Error";
            return null;
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

}