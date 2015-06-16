package com.example.fernando.myapplication.Entities;

import com.example.fernando.myapplication.Common.Constants;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

/**
 * Created by fernando on 19/04/15.
 */
public class Chat {
    public ArrayList<Message> messages;
    public String otherUser;

    public Chat(String otherUser) {
        this.messages = new ArrayList<>();
        this.otherUser = otherUser;
    }

    public JSONObject toJson() {  // AGREGAR MI PROPIO USERNAME AL JSON CHAT
        JSONObject jchat = new JSONObject();
        JSONArray jmessages = new JSONArray();
        try {
            jchat.put("username_2", otherUser);
            jchat.put("username_1", Constants.user.username);

            for (int i = 0; i < messages.size(); i++) {
                jmessages.put(messages.get(i).toJson());
            }

            jchat.put("messages", jmessages);

            return jchat;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static Chat toChat(JSONObject jsonChat) {
        try {
            Chat newChat;
            if (jsonChat.getString("username_1").compareTo(Constants.user.username) == 0) {
                newChat = new Chat(jsonChat.getString("username_2"));
            } else {
                newChat = new Chat(jsonChat.getString("username_1"));
            }

            JSONArray jsonMessages = jsonChat.getJSONArray("messages");

            for (int message = 0; message < jsonMessages.length(); message++) {

//                JSONObject object = new JSONObject(chats.get(chat).toString());
////                    JSONObject jsonObject = new JSONObject(username);
//
//                Chat newChat = Chat.toChat(object);
//
//                Constants.user.chats.add(newChat);

                if (jsonMessages.get(message).toString().compareTo("null") != 0) {
                    JSONObject oneMessage = new JSONObject(jsonMessages.get(message).toString());
                    Message newMessage = Message.toMessage(oneMessage);

                    newChat.messages.add(newMessage);
                }
            }

            return newChat;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

}
