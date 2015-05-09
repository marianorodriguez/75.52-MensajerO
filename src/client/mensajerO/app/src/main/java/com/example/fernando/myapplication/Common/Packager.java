package com.example.fernando.myapplication.Common;

import android.util.Base64;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.UnsupportedEncodingException;

/**
 * Created by fernando on 19/04/15.
 */
public class Packager {

    String otherUser;
    String message;

    private String toJson (String service, User user) {

        switch (service) {

            case "logIn":
                return user.toJsonForServer().toString();

            case "signUp":
                return user.toJsonForServer().toString();

            case "setConfig":
                return user.toJsonForServer(0).toString();

            case "somethingForMe":
                return user.toJsonForServer().toString();

            case "currentChats":
                return user.toJsonForServer().toString();

            case "users":
                return user.toJsonForServer().toString();

            case "sendMessage":
                return user.toJsonForServer(otherUser, message).toString();

        }
        return null;
    }

    public String wrap(String service, User user) {

        String jsonPackage = toJson(service, user);
        System.out.println(jsonPackage);

        byte[] data;
        try {
            data = jsonPackage.getBytes("UTF-8");
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
            return null;
        }

        String packageEncoded = Base64.encodeToString(data, Base64.NO_WRAP);
        packageEncoded = packageEncoded.replaceAll("(?:\\r\\n|\\n\\r|\\n|\\r)", "");

        return packageEncoded;
    }

    public String wrap(String service, User user, String otherUser, String message) {

        this.otherUser = otherUser;
        this.message = message;

        return wrap(service, user);

//        String jsonPackage = toJson(service, user);
//        System.out.println(jsonPackage);
//
//        byte[] data;
//        try {
//            data = jsonPackage.getBytes("UTF-8");
//        } catch (UnsupportedEncodingException e) {
//            e.printStackTrace();
//            return null;
//        }
//
//        String packageEncoded = Base64.encodeToString(data, Base64.NO_WRAP);
//        packageEncoded = packageEncoded.replaceAll("(?:\\r\\n|\\n\\r|\\n|\\r)", "");
//
//        return packageEncoded;
    }

    public String wrap(String response) {

        byte[] data;
        try {
            data = response.getBytes("UTF-8");
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
            return null;
        }

        String packageEncoded = Base64.encodeToString(data, Base64.NO_WRAP);
        packageEncoded = packageEncoded.replaceAll("(?:\\r\\n|\\n\\r|\\n|\\r)", "");

        return packageEncoded;
    }

    public String wrap(JSONObject response) {

        String resp = response.toString();

        return wrap(resp);

    }

    public JSONObject unwrap (String responsePackage) {

        int flags = Base64.NO_WRAP | Base64.URL_SAFE;
        byte[] jsonBytes = Base64.decode(responsePackage, flags);

//        System.out.println(json);
        String json = new String (jsonBytes);

        //json = "{\"ok\":\"true\",\"what\":\"\"}";


        try {
            JSONObject resp = new JSONObject(json);
            return resp;

        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public JSONArray unwrap (String responsePackage, String key) {

        int flags = Base64.NO_WRAP | Base64.URL_SAFE;
        byte[] jsonBytes = Base64.decode(responsePackage, flags);

//        System.out.println(json);
        String json = new String (jsonBytes);

        try {

            JSONObject package_ = new JSONObject(json);
            JSONArray jArray = (JSONArray) package_.get(key);

            return jArray;

        } catch (JSONException e) {
            e.printStackTrace();
        }
        JSONObject package_ = null;
        try {
            package_ = new JSONObject(json);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        JSONArray jArray = null;
        if (package_ != null) {
            try {
                jArray = (JSONArray) package_.get(key);
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }
        return jArray;
    }

}
