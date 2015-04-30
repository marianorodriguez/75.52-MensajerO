package com.example.fernando.myapplication.Common;

import android.util.Base64;

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

    public String wrap(JSONObject mockResponse) {

        String resp = mockResponse.toString();

        byte[] data;
        try {
            data = resp.getBytes("UTF-8");
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
            return null;
        }

        String packageEncoded = Base64.encodeToString(data, Base64.NO_WRAP);
        packageEncoded = packageEncoded.replaceAll("(?:\\r\\n|\\n\\r|\\n|\\r)", "");

        return packageEncoded;

    }

    public JSONObject unwrap (String responsePackage) {

        int flags = Base64.NO_WRAP | Base64.URL_SAFE;
        byte[] jsonBytes = Base64.decode(responsePackage, flags);

//        System.out.println(json);
        String json = new String (jsonBytes);

        try {
            JSONObject resp = new JSONObject(json);
            return resp;

        } catch (JSONException e) {
            e.printStackTrace();
        }
        return null;
    }

}
