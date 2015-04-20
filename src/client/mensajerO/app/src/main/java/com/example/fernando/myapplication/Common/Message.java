package com.example.fernando.myapplication.Common;

import android.text.format.Time;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.Date;

/**
 * Created by fernando on 19/04/15.
 */
public class Message {
    public Date date;
    public Time hour;
    public String emisor;
    public String text;

    public Message (String emisor, String text, Date date, Time hour) {
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

            return jmess;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }

    }
}
