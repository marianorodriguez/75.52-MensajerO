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

    public String username;
    public String password;
    public String profilePicture;
    public String location;
    public String status;
    JsonUtil jsonU;
    public ArrayList<Chat> chats;

    public User(String _username, String _password) {
        username = _username;
        password = _password;
        jsonU = new JsonUtil();
        chats = new ArrayList<Chat>();
    }

    public JSONObject toJsonForServer () {
        JSONObject juser = new JSONObject();
        try {
            juser.put("username", username);
            juser.put("password", password);

            return juser;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    public JSONObject toJsonForServer (int a) {
        JSONObject juser = toJsonForServer();
        try {
            juser.put("picture", profilePicture);
            juser.put("location", location);
            juser.put("status", status);

            return juser;
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