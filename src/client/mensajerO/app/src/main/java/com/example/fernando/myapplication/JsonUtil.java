package com.example.fernando.myapplication;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.List;

/**
 * Created by fernando on 4/04/15.
 */

public class JsonUtil {

    public static JSONObject toJSon(Person person) {
        try {
            // Here we convert Java Object to JSON
            JSONObject jsonObj = new JSONObject();
            jsonObj.put("name", person.getName()); // Set the first name/pair
            jsonObj.put("surname", person.getSurname());

            JSONObject jsonAdd = new JSONObject(); // we need another object to store the address
            jsonAdd.put("address", person.getAddress().getAddress());
            jsonAdd.put("city", person.getAddress().getCity());
            jsonAdd.put("state", person.getAddress().getState());

            // We add the object to the main object
            jsonObj.put("address", jsonAdd);

            // and finally we add the phone number
            // In this case we need a json array to hold the java list
            JSONArray jsonArr = new JSONArray();

            JSONObject pnObj = new JSONObject();
            pnObj.put("num", person.getNum1().getNumber());
            pnObj.put("type", person.getNum1().getType());
            jsonArr.put(pnObj);

            JSONObject pnObj2 = new JSONObject();
            pnObj2.put("num", person.getNum2().getNumber());
            pnObj2.put("type", person.getNum2().getType());
            jsonArr.put(pnObj2);

            jsonObj.put("phoneNumber", jsonArr);

            System.out.println(jsonObj);

            return jsonObj;

        } catch (JSONException ex) {
            ex.printStackTrace();
        }

        return null;

    }

    public static Person toPerson(JSONObject jsonObject) {
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
