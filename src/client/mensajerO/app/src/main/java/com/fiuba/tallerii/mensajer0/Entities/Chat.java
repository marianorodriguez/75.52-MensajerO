package com.fiuba.tallerii.mensajer0.Entities;

import com.fiuba.tallerii.mensajer0.Common.Constants;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

/**
 * Esta clase representa un chat entre dos usuarios. 
 */
public class Chat {
    public ArrayList<Message> messages;
    public String otherUser;

/**
* Crea un nuevo chat con el parámetro otherUser.
*/
    public Chat(String otherUser) {
        this.messages = new ArrayList<>();
        this.otherUser = otherUser;
    }
/**
* Convierte la clase en un objeto JSONObject
*/
    public JSONObject toJson() {
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
/**
* Desde un JSONObject se crea un chat. 
*/
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
