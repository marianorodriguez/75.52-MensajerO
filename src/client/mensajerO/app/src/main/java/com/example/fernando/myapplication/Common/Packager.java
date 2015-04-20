package com.example.fernando.myapplication.Common;

import android.util.Base64;

import java.io.UnsupportedEncodingException;

/**
 * Created by fernando on 19/04/15.
 */
public class Packager {

    public String toJson (String service, User user) {

        switch (service) {
            case "logIn":
                return user.toJsonToServer().toString();
            case "signUp":
                return user.toJsonToServer().toString();

            case "setConfig":
                return user.toJsonToServer().toString();

            case "somethingForMe":
                return user.toJsonToServer().toString();

            case "currentChats":
                return user.toJsonToServer().toString();

            case "users":
                return user.toJsonToServer().toString();

            case "sendMessage":
                return user.toJsonToServer().toString();

        }
        return null;
    }

    public String doPackage(String service, User user) {

        String jsonPackage= toJson(service, user);

        byte[] data = new byte[0];
        try {
            data = jsonPackage.getBytes("UTF-8");
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
            return null;
        }

        String packageEncoded = Base64.encodeToString(data, Base64.NO_WRAP);

        packageEncoded = packageEncoded.replaceAll("(?:\\r\\n|\\n\\r|\\n|\\r)", "");
//        System.out.println(packageEncoded);

        return packageEncoded;
    }

}
