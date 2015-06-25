package com.fiuba.tallerii.mensajer0.Entities;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Esta clase representa un mensaje entre dos usuarios. 
 */
public class Message {
    public String msg_date;
    public String msg_time;
    public String msg_fromID;
    public String msg_text;
    public String msg_toID;
/**
* Crea un nuevo mensaje. @param msg_fromID: el usuario que mando el mensaje, msg_toID: a quien, text: el mensaje , date: fecha y time:hora. 
*/
    public Message (String msg_fromID, String msg_toID, String text, String date, String time) {
        this.msg_fromID = msg_fromID;
        this.msg_toID = msg_toID;
        this.msg_text = text;
        this.msg_date = date;
        this.msg_time = time;
    }
/**
* Convierte un mensaje en un JSONObject
*/
    public JSONObject toJson() {
        JSONObject jmess = new JSONObject();
        try {
            jmess.put("msg_date", msg_date);
            jmess.put("msg_time", msg_time);
            jmess.put("msg_text", msg_text);
            jmess.put("msg_fromID", msg_fromID);
            jmess.put("msg_toID", msg_toID);

            return jmess;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }

    }
/**
* Crea un mensaje a partir de un JSONObject
*/
    public static Message toMessage(JSONObject jsonMessage) {
        try {
            Message newMessage = new Message(
                    jsonMessage.getString("msg_fromID"),
                    jsonMessage.getString("msg_toID"),
                    jsonMessage.getString("msg_text"),
                    jsonMessage.getString("msg_date"),
                    jsonMessage.getString("msg_time") );

            return newMessage;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }


    }

}
