package com.example.fernando.myapplication.Mocks;

import android.annotation.TargetApi;
import android.content.SharedPreferences;
import android.os.Build;
import android.util.ArrayMap;
import android.util.Pair;

import com.example.fernando.myapplication.Common.Chat;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Common.Message;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Calendar;

import android.content.SharedPreferences;

/**
 * Created by fernando on 01/05/15.
 */
@TargetApi(Build.VERSION_CODES.KITKAT)
public class Server {
    public ArrayList<String> loguedUsers = new ArrayList<>();

    // user para el qe es el message, mensajes
    ArrayList<Pair<String, ArrayList<Message>>> newMessages = new ArrayList<>();

    public Server() {

    }

    public String logIn (String userPackage) {

        boolean ok = true;
        JSONObject userP = Constants.packager.unwrap(userPackage);
        try {
            String username = userP.getString("username");
            if (!loguedUsers.contains(username))
                ok = false;

            JSONObject response = new JSONObject();
            if (ok)
                response.put("ok", "true");
            else
                response.put("ok", "false");

            String resp = Constants.packager.wrap(response);

            return resp;

        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    public String signUp (String userPackage) {
        boolean ok = true;
        JSONObject userP = Constants.packager.unwrap(userPackage);
        try {
            String username = userP.getString("username");
            if (loguedUsers.contains(username))
                ok = false;

            JSONObject response = new JSONObject();
            if (ok) {
                response.put("ok", "true");
                loguedUsers.add(username);
            }
            else
                response.put("ok", "false");

            String resp = Constants.packager.wrap(response);

            return resp;

        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    public String setConfig (String userPackage) {

        JSONObject userP = Constants.packager.unwrap(userPackage);
        try {
            JSONObject response = new JSONObject();

            response.put("ok", "true");

            String resp = Constants.packager.wrap(response);
            return resp;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    public String somethingForMe (String userPackage) {
        JSONObject userP = Constants.packager.unwrap(userPackage);

        try {
            String username = userP.getString("username");

            JSONObject response = new JSONObject();
            ArrayList<Message> newM = new ArrayList<>();

            for (int user = 0; user < newMessages.size(); user++) {
                if (newMessages.get(user).first.compareTo(username) == 0) {
                    newM = newMessages.get(user).second;
                    break;
                }
            }

            JSONArray messages = new JSONArray();

            for (int message = 0; message < newM.size(); message++) {
                JSONObject jsonMessage = newM.get(message).toJson();
                messages.put(jsonMessage);
            }

            response.put("messages", messages);

            newM.clear();

            String resp = Constants.packager.wrap(response);
            return resp;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    public String users (String userPackage) {
        JSONObject userP = Constants.packager.unwrap(userPackage);

        try {
            JSONArray users = new JSONArray();

            loguedUsers.remove(userP.getString("username"));

            for (int user = 0; user < loguedUsers.size(); user++) {
                users.put(loguedUsers.get(user));
            }

            loguedUsers.add(userP.getString("username"));

            JSONObject response = new JSONObject();
            response.put("users", users);

            String resp = Constants.packager.wrap(response);
            return resp;

        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    public String currentChats (String userPackage) {
        JSONObject userP = Constants.packager.unwrap(userPackage);

        try {
            String username = userP.getString("username");

            String jsonChats = Constants.mSharedPreferences.getString(username+"chats", "");

            String resp = Constants.packager.wrap(jsonChats);
            return resp;

        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }

    }

    public String sendMessage (String userPackage) {
        boolean founded = false;
        JSONObject userP = Constants.packager.unwrap(userPackage);

        try {
            String username = userP.getString("username");
            String msg_to = userP.getString("msg_to");
            String msg_text = userP.getString("msg_text");

            Calendar c = Calendar.getInstance();

            Message newMessage = new Message(username, msg_text,
                    c.getTime().toString(), "" );

            for (int user = 0; user < newMessages.size(); user++) {
                if (newMessages.get(user).first.compareTo(msg_to) == 0) {
                    newMessages.get(user).second.add(newMessage);
                    founded = true;
                    break;
                }
            }
            if (!founded) {
                newMessages.add(new Pair<>(msg_to, new ArrayList<Message>()));
                newMessages.get(newMessages.size()-1).second.add(newMessage);
            }

            JSONObject response = new JSONObject();

            response.put("ok", "true");

            String resp = Constants.packager.wrap(response);
            return resp;

        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

}
