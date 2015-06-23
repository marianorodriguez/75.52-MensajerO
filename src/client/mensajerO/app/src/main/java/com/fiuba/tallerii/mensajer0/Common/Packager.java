package com.fiuba.tallerii.mensajer0.Common;

import android.util.Base64;

import com.fiuba.tallerii.mensajer0.Entities.User;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.UnsupportedEncodingException;

/**
 * Created by fernando on 19/04/15.
 */
public class Packager {

    String msg_toID;
    String msg_text;
    String otherUser;

    private String toJson (String service, User user) {

        switch (service) {

            case "logIn":
                return user.toJsonForServer().toString();

            case "signUp":
                return user.toJsonForServer(0).toString();

            case "setConfig":
                return user.toJsonForServer(0).toString();

            case "somethingForMe":
                return user.toJsonForServer().toString();

            case "currentChats":
                return user.toJsonForServer().toString();

            case "users":
                return user.toJsonForServer().toString();

            case "sendMessage":
                return user.toJsonForServer(msg_toID, msg_text).toString();

            case "deleteChat":
                return user.toJsonForServer(otherUser).toString();
        }
        return null;
    }

    public String wrap(String service, User user) {

        String jsonPackage = toJson(service, user);

        byte[] data;
        try {
            data = jsonPackage.getBytes("UTF-8");
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
            return null;
        }

        String packageEncoded = Base64.encodeToString(data, Base64.DEFAULT);
        packageEncoded = packageEncoded.replaceAll("(?:\\r\\n|\\n\\r|\\n|\\r)", "");

        return packageEncoded;
    }

    public String wrap(String service, User user, String msg_toID, String msg_text) {

        this.msg_toID = msg_toID;
        this.msg_text = msg_text;
        this.otherUser = msg_toID;

        return wrap(service, user);
    }

    public String wrap(String response) {

        byte[] data;
        try {
            data = response.getBytes("UTF-8");
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
            return null;
        }

        String packageEncoded = Base64.encodeToString(data, Base64.DEFAULT);
        packageEncoded = packageEncoded.replaceAll("(?:\\r\\n|\\n\\r|\\n|\\r)", "");

        return packageEncoded;
    }

    public String wrap(JSONObject response) {

        String resp = response.toString();

        return wrap(resp);

    }

    public JSONObject unwrap (String responsePackage) {

        byte[] jsonBytes = Base64.decode(responsePackage, Base64.DEFAULT);

        String json = new String (jsonBytes);

        try {
            JSONObject resp = new JSONObject(json);
            return resp;

        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public JSONArray unwrap (String responsePackage, String key) {

        byte[] jsonBytes = Base64.decode(responsePackage, Base64.DEFAULT);

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
