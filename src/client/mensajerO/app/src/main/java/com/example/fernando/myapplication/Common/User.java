package com.example.fernando.myapplication.Common;

import android.graphics.Bitmap;
import android.util.Base64;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;
import java.util.ArrayList;

/**
 * Created by fernando on 19/04/15.
 */
public class User {

    public String username = "";
    public String password = "";
    public Bitmap profilePicture = null;
    public String location;
    public String status;
    public ArrayList<Chat> chats;

    public User(String username, String password) {
        this.username = username;
        this.password = password;
        this.chats = new ArrayList<>();
    }

    public User(String username) {
        this.username = username;
    }

    public JSONObject toJsonForServer () {
        JSONObject juser_ = new JSONObject();
        try {
            juser_.put("username", username);
            juser_.put("password", password);
            juser_.put("location", location);

            return juser_;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    public JSONObject toJsonForServer (int flag) {
        JSONObject juser_ = toJsonForServer();
        try {
            juser_.put("picture", setPicture(profilePicture));
            juser_.put("status", status);

            return juser_;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    private String setPicture(Bitmap pictureBitmap) {

        ByteArrayOutputStream baos = new  ByteArrayOutputStream();
        pictureBitmap.compress(Bitmap.CompressFormat.PNG, 100, baos);
        byte [] b = baos.toByteArray();
        String temp = Base64.encodeToString(b, Base64.NO_WRAP);
        temp = temp.replaceAll("(?:\\r\\n|\\n\\r|\\n|\\r)", "");

        return temp;
    }

    public JSONObject toJsonForServer (String msg_toID, String msg_text) {
//        JSONObject juser_ = toJsonForServer();
        JSONObject jmessage = new JSONObject();
        try {
            jmessage.put("msg_fromID", username);
            jmessage.put("msg_toID", msg_toID);
            jmessage.put("msg_text", msg_text);
            jmessage.put("msg_date", "");
            jmessage.put("msg_time", "");

            return jmessage;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    public JSONObject toJsonForDisk () {
        JSONObject juser = toJsonForServer(0);
        JSONArray jchats = new JSONArray();
        for (int i = 0; i < chats.size(); i++) {
            jchats.put(chats.get(i).toJson());
        }
        try {
            juser.put("chats", jchats);

            return juser;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    public JSONObject chatsToJson () {
        JSONObject allChats = new JSONObject();
        JSONArray jchats = new JSONArray();
        for (int i = 0; i < chats.size(); i++) {
            jchats.put(chats.get(i).toJson());
        }
        try {
            allChats.put("chats", jchats);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return allChats;
    }

    public static User toUser(JSONObject jsonObject) {
        try {
            User newUser = new User(jsonObject.getString("username"));

            newUser.location = jsonObject.getString("location");
            newUser.location = jsonObject.getString("picture");
            newUser.location = jsonObject.getString("status");

            return newUser;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }
}