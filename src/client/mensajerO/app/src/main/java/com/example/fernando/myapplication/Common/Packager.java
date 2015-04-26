package com.example.fernando.myapplication.Common;

import android.util.Base64;

import java.io.UnsupportedEncodingException;

/**
 * Created by fernando on 19/04/15.
 */
public class Packager {

    private String toJson (String service, User user) {

        switch (service) {
            case "logIn":
                return user.toJsonForServer().toString();
            case "signUp":
                return user.toJsonForServer().toString();

            case "setConfig":
                return user.toJsonForServer().toString();

            case "somethingForMe":
                return user.toJsonForServer().toString();

            case "currentChats":
                return user.toJsonForServer().toString();

            case "users":
                return user.toJsonForServer().toString();

            case "sendMessage":
                return user.toJsonForServer().toString();

        }
        return null;
    }

    public String doPackage(String service, User user) {

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

}
