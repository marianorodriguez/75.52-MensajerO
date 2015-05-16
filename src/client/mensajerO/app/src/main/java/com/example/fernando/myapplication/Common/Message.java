package com.example.fernando.myapplication.Common;

import android.text.format.Time;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.Date;

/**
 * Created by fernando on 19/04/15.
 */
public class Message {
    public String date;
    public String hour;
    public String emisor;
    public String text;

    public Message (String emisor, String text, String date, String hour) {
        this.emisor = emisor;
        this.text = text;
        this.date = date;
        this.hour = hour;
    }

    public JSONObject toJson() {
        JSONObject jmess = new JSONObject();
        try {
            jmess.put("date", date.toString());
            jmess.put("hour", hour.toString());
            jmess.put("text", text);
            jmess.put("emisor", emisor);

            return jmess;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }

    }

    public static Message toMessage(JSONObject jsonMessage) {
        try {
            Message newMessage = new Message(
                    jsonMessage.getString("msg_fromID"),
                    jsonMessage.getString("text"),
                    jsonMessage.getString("date"),
                    jsonMessage.getString("hour") );

            return newMessage;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }


    }

}
