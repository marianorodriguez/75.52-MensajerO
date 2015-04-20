package com.example.fernando.myapplication.Common;

import android.content.Context;
import android.util.ArrayMap;
import android.util.Pair;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Map;

/**
 * Created by fernando on 4/04/15.
 */

public class JsonUtil {

    public JSONObject toJSon(User user) {
        try {
            // Here we convert Java Object to JSON

            JSONObject jsonU = new JSONObject();
            jsonU.put("username", user.username); // Set the first name/pair
            jsonU.put("password", user.password);
            jsonU.put("location", user.location);
            jsonU.put("status", user.status);
            jsonU.put("picture", user.profilePicture);

            return jsonU;

        } catch (JSONException ex) {
            ex.printStackTrace();
        }
        return null;
    }

    public JSONObject toJSon(User user, ArrayList<Chat> chats) {

        JSONObject jsonU = toJSon(user);
        JSONArray allChats = new JSONArray();

        try {

            for (int i = 0; i < chats.size(); i++) {

                JSONObject chat = new JSONObject();

                chat.put("otherUsername", chats.get(i).otherUser);

                for (int j = 0; j < chats.get(i).messages.size(); j++) {

                }

                allChats.put(chat);
            }

            jsonU.put("chats", allChats);
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }

        return jsonU;
    }

    public Person toMessage(JSONObject jsonObject) {
        try {
            Person person = new Person();
            person.setName(jsonObject.getString("name"));
            person.setSurname(jsonObject.getString("surname"));

            person.getAddress().setCity(jsonObject.getJSONObject("address").getString("city"));
            person.getAddress().setAddress(jsonObject.getJSONObject("address").getString("address"));
            person.getAddress().setState(jsonObject.getJSONObject("address").getString("state"));

            JSONArray jArr = jsonObject.getJSONArray("phoneNumber");

            person.getNum1().setNumber(jArr.getJSONObject(0).getString("num"));
            person.getNum1().setType(jArr.getJSONObject(0).getString("type"));

            person.getNum2().setNumber(jArr.getJSONObject(1).getString("num"));
            person.getNum2().setType(jArr.getJSONObject(1).getString("type"));
            return person;

        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }

    }

}
