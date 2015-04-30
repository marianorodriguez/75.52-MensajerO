package com.example.fernando.myapplication.Mocks;

import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Common.User;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

/**
 * Created by fernando on 27/04/15.
 */
public class Mocks {

    public static String LogInResponseOK;
    public static String LogInResponseWRONG;
    public static String currentChatsResponse;

    public static String SingUpResponseOK;
    public static String SingUpResponseWRONG;

    public static String ConfigResponseOK;
    public static String ConfigResponseWRONG;

    public static String SomethingForMeResponse;
    public static String UsersResponse;

    public static String sendMessageResponseOK;
    public static String sendMessageResponseWRONG;
    public static ArrayList<User> otherUsers = new ArrayList<>();

    public Mocks() {

    }

    public static String wrapLogInResponse(String bool) {

        JSONObject resp = new JSONObject();
        try {
            resp.put("ok", bool);

            return Constants.packager.wrap(resp);
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static void createFakeUsers() {
        User newUser = new User("juancito");
        otherUsers.add(newUser);
        newUser = new User("fernando");
        otherUsers.add(newUser);
        newUser = new User("mariano");
        otherUsers.add(newUser);
    }

    private String wrapCurrentChats() {
        return "";
    }

    private String wrapSignUpResponse() {
        return "";
    }

    private String wrapConfigResponse() {
        return "";
    }

}
