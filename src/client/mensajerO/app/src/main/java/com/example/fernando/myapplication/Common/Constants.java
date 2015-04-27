package com.example.fernando.myapplication.Common;

import android.content.SharedPreferences;
import android.support.v4.util.Pair;

import java.util.ArrayList;

/**
 * Created by fernando on 22/04/15.
 */
final public class Constants//final to prevent instantiation
{
    public static String ipServer = "127.0.0.1";
    public static String portServer = "8080";
    public static final String logInUrl = "http://"+ipServer+":"+portServer+"+/logIn";
    public static final String signUpUrl = "http://"+ipServer+":"+portServer+"+/signUp";
    public static final String currentChatsUrl = "http://"+ipServer+":"+portServer+"+/currentChats";
    public static final String setConfigUrl = "http://"+ipServer+":"+portServer+"+/setConfig";
    public static final String somethingForMeUrl = "http://"+ipServer+":"+portServer+"+/somethingForMe";
    public static final String usersUrl = "http://"+ipServer+":"+portServer+"+/users";
    public static final String sendMessageUrl = "http://"+ipServer+":"+portServer+"+/sendMessage";
    public static User user = null;

    public static SharedPreferences mSharedPreferences;
    public static final String PREFS = "prefs";
    public static final String PREF_NAME = "name";
    public static final String PREF_PASS = "password";

    public static final Packager packager = new Packager();
    public static ArrayList<Pair<String, String>> users = new ArrayList<>();
    public static final ChatEditor chatEditor = new ChatEditor();

    //private constructor to prevent instantiation/inheritance
    private Constants() {}

}
