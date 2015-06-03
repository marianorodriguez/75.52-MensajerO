package com.example.fernando.myapplication.Common;

import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Base64;
import android.widget.ListView;

import com.example.fernando.myapplication.Activities.ChatsHallActivity;
import com.example.fernando.myapplication.Activities.UsersActivity;
import com.example.fernando.myapplication.Entities.Chat;
import com.example.fernando.myapplication.Entities.User;
import com.example.fernando.myapplication.Mocks.Server;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

/**
 * Created by fernando on 22/04/15.
 */
final public class Constants//final to prevent instantiation
{
    public static String ipServer = "192.168.1.100";
    public static String portServer = "8081";
    public static final String logInUrl = "http://" + ipServer +":" + portServer + "/logIn";
    public static final String signUpUrl = "http://" + ipServer + ":" + portServer + "/signUp";
    public static final String currentChatsUrl = "http://" + ipServer+ ":" +portServer + "/currentChats";
    public static final String setConfigUrl = "http://" + ipServer + ":" + portServer + "/setConfig";
    public static final String somethingForMeUrl = "http://" + ipServer + ":" + portServer + "/somethingForMe";
    public static final String usersUrl = "http://" + ipServer + ":" + portServer + "/users";
    public static final String sendMessageUrl = "http://" + ipServer + ":" + portServer + "/sendMessage";

    public static User user = null;

//    public static SharedPreferences mSharedPreferences;
    public static final String PREFS = "prefs";
    public static final String PREF_NAME = "name";
    public static final String PREF_PASS = "password";
//    public static final String PREF_CHATS = "chats";
//    private static final String PREF_USERS = "users";

    public static final Packager packager = new Packager();
    public static ArrayList<User> otherUsers = new ArrayList<>();
    public static final ChatEditor chatEditor = new ChatEditor();

    public static String logInOk = "";
    public static String logInStatus = "";
    public static String logInPicture = "";
    public static String logInLocation = "";

    public static String currentChatsOk = "";

    public static String signUpOk = "";
    public static String signUpLocation;

    public static String configOK = "";

    public static String sendMessageOk = "";
    public static String chatWith = "";

    public static ListView chatListView = null;
    public static ChatsHallActivity.StableArrayAdapter chatsAdapter = null;
    public static ListView usersListView = null;
    public static UsersActivity.StableArrayAdapter usersAdapter = null;

//    public static Server server = null;
    public static Server server = new Server(); //si no pones en null

    //La cantidad actual de chats renderizados hasta el momento
    public static int currentChatsSize = 0;
    //La cantidad actual de users renderizados hasta el momento
    public static int currentUsersSize = 0;
    //La cantidad actual de messages en un chat x renderizados hasta el momento
    public static int messagesSize = 0;

    //private constructor to prevent instantiation/inheritance
    private Constants() {}

    public static void initialize(SharedPreferences mSharedPref) {

        String username = mSharedPref.getString(PREF_NAME, "");
        String password = mSharedPref.getString(PREF_PASS, "");
        Constants.user = new User(username, password);
        Constants.user.status = mSharedPref.getString(username+"status", "");
        Constants.user.location = mSharedPref.getString(username+"location", "");
        Constants.user.profile_picture = stringToBitmap(mSharedPref.getString(username + "profile_picture", ""));

        try {

            JSONObject chatsObject = new JSONObject(mSharedPref.getString(username+"chats", ""));
            JSONArray chats = (JSONArray) chatsObject.get("chats");
//            JSONArray chats = new JSONArray(mSharedPref.getString(username+"chats", ""));

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

    private static Bitmap stringToBitmap(String stringPicture) {
        try {
            byte [] encodeByte = Base64.decode(stringPicture, Base64.DEFAULT);
            Bitmap bitmap = BitmapFactory.decodeByteArray(encodeByte, 0, encodeByte.length);
            return bitmap;
        } catch(Exception e) {
            e.getMessage();
            return null;
        }
    }

    public static void reset() {

        user = null;

        logInOk = "";
        currentChatsOk = "";

        signUpOk = "";
        configOK = "";

        sendMessageOk = "";
        chatWith = "";

        chatListView = null;
        chatsAdapter = null;
        usersListView = null;
        usersAdapter = null;

        currentChatsSize = 0;
        //La cantidad actual de users renderizados hasta el momento
        currentUsersSize = 0;
        //La cantidad actual de messages en un chat x renderizados hasta el momento
        messagesSize = 0;

        otherUsers.clear();

    }

}
