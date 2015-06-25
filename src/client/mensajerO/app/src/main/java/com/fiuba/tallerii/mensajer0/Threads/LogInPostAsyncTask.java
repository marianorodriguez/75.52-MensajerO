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
 * Clase usada para hacer la conexion con el servidor cuando se realiza la actividad de logIn de usuario.
 */
public class LogInPostAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {

    @Override
    protected String doInBackground(Pair<Context, String>... params) {

        if ( Constants.server != null ) {
            String response = Constants.server.logIn(params[0].second);

            try {

                JSONObject resp = Constants.packager.unwrap(response);

                Constants.logInOk = resp.getString("ok");
                Constants.logInPicture = resp.getString("profile_picture");
                Constants.logInStatus = resp.getString("status");
                Constants.logInLocation = resp.getString("location");

                return "";

            } catch (JSONException e) {
                e.printStackTrace();
            }
            return null;
        } else {
            HttpResponse response = doRequest(params);

            if (response != null && response.getStatusLine().getStatusCode() == 200) {
                try {

                    JSONObject respons = Constants.packager.unwrap(
                            EntityUtils.toString(response.getEntity()));

                    Constants.logInOk = respons.getString("ok");
                    if(Constants.logInOk.compareTo("true")==0) {
                        Constants.logInPicture = respons.getString("profile_picture");
                        Constants.logInStatus = respons.getString("status");
                        Constants.logInLocation = respons.getString("location");
                    }

                    return "";

                } catch (JSONException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            Constants.logInOk = "Error";
            return null;
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
