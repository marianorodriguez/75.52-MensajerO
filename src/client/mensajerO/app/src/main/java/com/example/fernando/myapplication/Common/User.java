package com.example.fernando.myapplication.Common;

import android.util.Pair;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

/**
 * Created by fernando on 19/04/15.
 */
public class User {

    public String username = "";
    public String password = "";
    public String profilePicture;
    public String location;
    public String status;
    JsonUtil jsonU;
    public ArrayList<Chat> chats;

    public User(String _username, String _password) {
        username = _username;
        password = _password;
        jsonU = new JsonUtil();
        chats = new ArrayList<>();
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
            juser_.put("picture", profilePicture);
            juser_.put("status", status);

            return juser_;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    public JSONObject toJsonForServer (String otherUser, String message) {
        JSONObject juser_ = toJsonForServer();
        try {
            juser_.put("msg_toID", otherUser);
            juser_.put("msg_text", message);

            return juser_;
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

}