package com.fiuba.tallerii.mensajer0.Entities;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Base64;

import com.fiuba.tallerii.mensajer0.Common.Constants;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;

/**
 * Created by fernando on 19/04/15.
 */
public class User {

    public String username = "";
    public String password = "";
    public Bitmap profile_picture = null;
    public String location;
    public String status;
    public String lastTimeConnected = "lastTimeConnected";
    public ArrayList<Chat> chats;

    public User(String username, String password) {
        this.username = username;
        this.password = password;
        this.chats = new ArrayList<>();
    }

    public User(String username) {
        this.username = username;
    }

    public User(String username, String status, String profile_picture, String location, String lastTimeConnected) {
        this.username = username;
        this.status = status;
        this.profile_picture = stringToBitmap(profile_picture);
        this.location = location;
        this.lastTimeConnected = getLastTimeConnected(lastTimeConnected);
    }

    // En este metodo se haria la conversion de segundos a la fecha y hora corresp
    private String getLastTimeConnected(String lastTimeConnected) {
        Calendar c = Calendar.getInstance();

        Long actualSeconds = c.getTimeInMillis()/1000;
        Long seconds = Long.parseLong(lastTimeConnected);

        if ((actualSeconds - seconds) < 60) {
            return "NOW";
        }

        Date date = new Date(seconds*1000);

        String intMonth = (String) android.text.format.DateFormat.format("MM", date);
        String day = (String) android.text.format.DateFormat.format("dd", date);
        String min = (String) android.text.format.DateFormat.format("mm", date);

        String[] parts = date.toString().split(" ");
        String[] parts2 = parts[3].split(":");
        String hour2 = parts2[0];

        return intMonth+"/"+day+" - "+ hour2 +":"+min;
    }

    public User(JSONObject jsonObject) {
        toUser(jsonObject);
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
            juser_.put("profile_picture", setPicture(profile_picture));
            juser_.put("status", status);

            return juser_;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    public JSONObject toJsonForServer (String otherUser) {
        JSONObject juser_ = toJsonForServer();
        try {
            juser_.put("otherUser", otherUser);
            return juser_;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    private String setPicture(Bitmap pictureBitmap) {

        if (pictureBitmap == null) return "";

        ByteArrayOutputStream baos = new  ByteArrayOutputStream();
        pictureBitmap.compress(Bitmap.CompressFormat.PNG, 100, baos);
        byte [] b = baos.toByteArray();
        String temp = Base64.encodeToString(b, Base64.DEFAULT);
        temp = temp.replaceAll("(?:\\r\\n|\\n\\r|\\n|\\r)", "");

        return temp;
    }

    public JSONObject toJsonForServer (String msg_toID, String msg_text) {
//        JSONObject juser_ = toJsonForServer();
        JSONObject jmessage = new JSONObject();
        try {
            jmessage.put("msg_fromID", username);
            jmessage.put("username", username);
            jmessage.put("password", Constants.user.password);
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
            newUser.profile_picture = newUser.stringToBitmap(jsonObject.getString("profile_picture"));
            newUser.status = jsonObject.getString("status");
            newUser.lastTimeConnected = newUser.getLastTimeConnected(jsonObject.getString("lastTimeConnected"));

            return newUser;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    public Bitmap stringToBitmap(String pictureString){
        try {
            byte [] encodeByte = Base64.decode(pictureString, Base64.DEFAULT);
            Bitmap bitmap = BitmapFactory.decodeByteArray(encodeByte, 0, encodeByte.length);
            return bitmap;
        } catch(Exception e) {
            e.getMessage();
            return null;
        }
    }

}