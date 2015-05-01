package com.example.fernando.myapplication.Mocks;

import android.annotation.TargetApi;
import android.os.Build;
import android.util.ArrayMap;

import com.example.fernando.myapplication.Common.Chat;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Common.Message;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

/**
 * Created by fernando on 01/05/15.
 */
public class Server {
    ArrayList<String> loguedUsers;

    // user para el qe es el message, mensajes
    ArrayMap<String, ArrayList<Message>> newMessages;

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

    @TargetApi(Build.VERSION_CODES.KITKAT)
    public String somethingForMe (String userPackage) {
        JSONObject userP = Constants.packager.unwrap(userPackage);

        try {

            String username = userP.getString("username");

            JSONObject response = new JSONObject();

            ArrayList<Message> newM = newMessages.get(username);
            JSONArray messages = new JSONArray();

            for (int message = 0; message < newM.size(); message++) {
                JSONObject jsonMessage = newM.get(message).toJson();
                messages.put(jsonMessage);
            }

            response.put("messages", messages);

            newMessages.get(username).clear();

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

            for (int user = 0; user < loguedUsers.size(); user++) {
                users.put(loguedUsers.get(user));
            }

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

            String jsonChats = Constants.mSharedPreferences.getString(username, "");

            String resp = Constants.packager.wrap(jsonChats);
            return resp;

        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }

    }

    @TargetApi(Build.VERSION_CODES.KITKAT)
    public String sendMessage (String userPackage) {
        JSONObject userP = Constants.packager.unwrap(userPackage);

        try {
            String username = userP.getString("username");
            String msg_to = userP.getString("msg_to");
            String msg_text = userP.getString("msg_text");

            Message newMessage = new Message(username, msg_text,
                    "date", "hour");

            newMessages.get(msg_to).add(newMessage);

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
