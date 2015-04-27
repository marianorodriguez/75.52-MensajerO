package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.content.SharedPreferences;
import android.net.http.AndroidHttpClient;
import android.os.AsyncTask;
import android.util.Pair;
import android.widget.Toast;

import com.example.fernando.myapplication.Activities.LogInActivity;

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

import java.io.IOException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

/**
 * Created by fernando on 3/04/15.
 */
public class ServletPostAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {
    private Context context;

    @Override
    protected String doInBackground(Pair<Context, String>... params) {
//        context = params[0].first;
//        String name = params[0].second;
//
//        String url = params[1].second;
//
//        String type = params[2].second;
//
//        HttpClient httpClient = new DefaultHttpClient();
//        HttpPost httpPost = new HttpPost(url); // 10.0.2.2 is localhost's IP address in Android emulator
//        HttpGet httpGet = new HttpGet("http://10.0.2.2:8080/hello");
//
//        ArrayList<String> a = new ArrayList<>();
//        a.add("lala");
//        a.add("lala2");
//        publishProgress("fer", "fer2", a.get(0));
//
////        while (!isCancelled()) {
////
////        }
//
//        System.out.println("SALIO");
//
//        try {
//            // Add name data to request
//            List<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>(1);
//            nameValuePairs.add(new BasicNameValuePair("name", name));
//            httpPost.setEntity(new UrlEncodedFormEntity(nameValuePairs));
//
//            // Execute HTTP Post Request
//            HttpResponse response = httpClient.execute(httpPost);
//            if (response.getStatusLine().getStatusCode() == 200) {
//                return EntityUtils.toString(response.getEntity());
//            }
//            return "Error: " + response.getStatusLine().getStatusCode() + " " + response.getStatusLine().getReasonPhrase();
//
////            // Execute HTTP GET Request
////            HttpResponse responseGET = httpClient.execute(httpGet);
////            if (responseGET.getStatusLine().getStatusCode() == 200) {
////                return EntityUtils.toString(responseGET.getEntity());
////            }
////            return "Error: " + responseGET.getStatusLine().getStatusCode() + " " + responseGET.getStatusLine().getReasonPhrase();
//
//        } catch (ClientProtocolException e) {
//            return e.getMessage();
//        } catch (IOException e) {
//            return e.getMessage();
//        }
        return "";
    }

    @Override
    protected void onProgressUpdate(String... values) {
        super.onProgressUpdate(values);

        System.out.println("VALUES = " + values[0] + "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
    }

    @Override
    protected void onPostExecute(String result) {
        // aca desempaqueto el packagela respuesta

        // LogInActivity.ok = result.toJson().buscar clave "ok"

//        Toast.makeText(context, result, Toast.LENGTH_LONG).show();
//        publishProgress("fer", "fer2", "carlos");
    }
}
