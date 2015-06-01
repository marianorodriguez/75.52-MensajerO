package com.example.fernando.myapplication.Mocks;

import android.annotation.TargetApi;
import android.content.SharedPreferences;
import android.os.Build;
import android.util.ArrayMap;
import android.util.Pair;

import com.example.fernando.myapplication.Common.Chat;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Common.Message;
import com.example.fernando.myapplication.Common.User;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Calendar;

import android.content.SharedPreferences;
import android.content.SharedPreferences;

/**
 * Created by fernando on 01/05/15.
 */
@TargetApi(Build.VERSION_CODES.KITKAT)
public class Server {

    public ArrayList<String> loguedUsers = new ArrayList<>();

    // user para el qe es el message, mensajes
    ArrayList<Pair<String, ArrayList<Message>>> newMessages = new ArrayList<>();
    SharedPreferences mSharedPrefs;

    public Server() {}

    public void setSharedPref(SharedPreferences mSharedPrefs) {
        this.mSharedPrefs = mSharedPrefs;
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

            response.put("location", getRealWorldLocation(userP.getString("location")));
            response.put("profile_picture", mSharedPrefs.getString(username+"profile_picture", ""));
            response.put("status", mSharedPrefs.getString(username+"status", ""));

            String resp = Constants.packager.wrap(response);

            return resp;

        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    private String getRealWorldLocation(String location) {
        return "San Telmo";
    }

    public String signUp (String userPackage) {
        boolean ok = true;
        JSONObject userP = Constants.packager.unwrap(userPackage);
        try {
            String username = userP.getString("username");
            String profile_picture = userP.getString("profile_picture");
            String location = userP.getString("location");
            String status = userP.getString("status");

            SharedPreferences.Editor e = mSharedPrefs.edit();
            e.putString(username+"location", location);
            e.putString(username+"profile_picture", profile_picture);
            e.putString(username+"chats", "");
            e.putString(username+"status", status);
            e.commit();

            if (loguedUsers.contains(username))
                ok = false;

            JSONObject response = new JSONObject();
            if (ok) {
                response.put("ok", "true");
                loguedUsers.add(username);
            }
            else
                response.put("ok", "false");

            response.put("location", getRealWorldLocation(location));

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

    private String deleteChat (String userPackage) {

        return null;
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
            // TAMBIEN SE LIMPIA DE newMessages ?????
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
                String username = loguedUsers.get(user);
                User newUser = new User(username,
                        mSharedPrefs.getString(username+"status", ""),
                        mSharedPrefs.getString(username+"profile_picture", ""),
                        mSharedPrefs.getString(username+"location", ""),
                        mSharedPrefs.getString(username+"lastTimeConnected", ""));
                JSONObject newUserJson = newUser.toJsonForServer(0);
                users.put(newUserJson);
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

        String resp = Constants.packager.wrap(
                mSharedPrefs.getString(Constants.user.username+"chats", ""));
        return resp;

    }

    public String sendMessage (String userPackage) {
        boolean founded = false;
        JSONObject userP = Constants.packager.unwrap(userPackage);

        try {
            String msg_fromID = userP.getString("msg_fromID");
            String msg_toID = userP.getString("msg_toID");
            String msg_text = userP.getString("msg_text");

            Calendar c = Calendar.getInstance();

            Message newMessage = new Message(msg_fromID, msg_toID, msg_text,
                    c.getTime().toString(), "" );

            for (int user = 0; user < newMessages.size(); user++) {
                if (newMessages.get(user).first.compareTo(msg_toID) == 0) {
                    newMessages.get(user).second.add(newMessage);
                    founded = true;
                    break;
                }
            }
            if (!founded) {
                newMessages.add(new Pair<>(msg_toID, new ArrayList<Message>()));
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
