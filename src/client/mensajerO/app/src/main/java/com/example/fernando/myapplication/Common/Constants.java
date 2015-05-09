package com.example.fernando.myapplication.Common;

import android.content.SharedPreferences;
import android.widget.ListView;

import com.example.fernando.myapplication.Activities.ChatsHallActivity;
import com.example.fernando.myapplication.Activities.UsersActivity;
import com.example.fernando.myapplication.Mocks.Server;

import org.json.JSONArray;
import org.json.JSONException;

import java.util.ArrayList;

/**
 * Created by fernando on 22/04/15.
 */
final public class Constants//final to prevent instantiation
{
    public static String ipServer = "192.168.1.104";
    public static String portServer = "8081";
    public static final String logInUrl = "http://" + ipServer +":" + portServer + "/logIn";
    public static final String signUpUrl = "http://" + ipServer + ":" + portServer + "/signUp";
    public static final String currentChatsUrl = "http://" + ipServer+ ":" +portServer + "/currentChats";
    public static final String setConfigUrl = "http://" + ipServer + ":" + portServer + "/setConfig";
    public static final String somethingForMeUrl = "http://" + ipServer + ":" + portServer + "/somethingForMe";
    public static final String usersUrl = "http://" + ipServer + ":" + portServer + "/users";
    public static final String sendMessageUrl = "http://" + ipServer + ":" + portServer + "/sendMessage";

    public static User user = null;

    public static SharedPreferences mSharedPreferences;
    public static final String PREFS = "prefs";
    public static final String PREF_NAME = "name";
    public static final String PREF_PASS = "password";
//    public static final String PREF_CHATS = "chats";
//    private static final String PREF_USERS = "users";

    public static final Packager packager = new Packager();
    public static ArrayList<User> otherUsers = new ArrayList<>();
    public static final ChatEditor chatEditor = new ChatEditor();
    public static String logInOk = "";
    public static String currentChatsOk = "";

    public static String signUpOk = "";
    public static String configOK = "";

    public static String sendMessageOk = "";
    public static String chatWith = "";

    public static ListView chatListView = null;
    public static ChatsHallActivity.StableArrayAdapter chatsAdapter = null;
    public static ListView usersListView = null;
    public static UsersActivity.StableArrayAdapter usersAdapter = null;

    public static Server server = null;

    public static int currentChatsSize = 0;
    public static int currentUsersSize;
    public static int messagesSize;

    //private constructor to prevent instantiation/inheritance
    private Constants() {}

    public static void initialize() {

        String username = Constants.mSharedPreferences.getString(PREF_NAME, "");
        String password = Constants.mSharedPreferences.getString(PREF_PASS, "");
        Constants.user = new User(username, password);

        try {
            JSONArray chats = new JSONArray(Constants.mSharedPreferences.getString(username+"chats", ""));

            for (int chat = 0; chat < chats.length(); chat++) {
                Constants.user.chats.add(Chat.toChat((org.json.JSONObject) chats.get(chat)));
            }

//            JSONArray users = new JSONArray(Constants.mSharedPreferences.getString(PREF_USERS, ""));
//
//            for (int user = 0; user < users.length(); user++) {
//                Constants.otherUsers.add(User.toUser((org.json.JSONObject) users.get(user)));
//            }

        } catch (JSONException e) {
            e.printStackTrace();
        }
    }
}
