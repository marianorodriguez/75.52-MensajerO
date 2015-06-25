package com.fiuba.tallerii.mensajer0.Common;

import android.content.SharedPreferences;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Base64;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.ScrollView;

import com.fiuba.tallerii.mensajer0.Activities.ChatsHallActivity;
import com.fiuba.tallerii.mensajer0.Entities.Chat;
import com.fiuba.tallerii.mensajer0.Entities.User;
import com.fiuba.tallerii.mensajer0.Mocks.Server;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

/**
 * Created by fernando on 22/04/15.
 */
final public class Constants//final to prevent instantiation
{
    public static String ipServer;
    public static String portServer = "8081";
    public static  String logInUrl = "http://" + ipServer +":" + portServer + "/logIn";
    public static  String signUpUrl = "http://" + ipServer + ":" + portServer + "/signUp";
    public static  String currentChatsUrl = "http://" + ipServer+ ":" +portServer + "/currentChats";
    public static  String setConfigUrl = "http://" + ipServer + ":" + portServer + "/setConfig";
    public static  String somethingForMeUrl = "http://" + ipServer + ":" + portServer + "/somethingForMe";
    public static  String usersUrl = "http://" + ipServer + ":" + portServer + "/users";
    public static  String sendMessageUrl = "http://" + ipServer + ":" + portServer + "/sendMessage";
    public static String deleteChatUrl = "http://" + ipServer + ":" + portServer + "/deleteChat";
    public static String broadcastUrl = "http://" + ipServer + ":" + portServer + "/broadcast";

    public static User user = null;

    public static final String PREFS = "prefs";
    public static final String PREF_NAME = "name";
    public static final String PREF_PASS = "password";

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
    public static String deleteOk = "";

    public static String sendMessageOk = "";
    public static String chatWith = "";

    public static ListView chatListView = null;
    public static ChatsHallActivity.StableArrayAdapter chatsAdapter = null;
    public static LinearLayout usersListView = null;
    public static ScrollView usersScroll = null;

    public static Server server = null;
//  public static Server server = new Server(); //SERVER MOCK

    //La cantidad actual de chats renderizados hasta el momento
    public static int currentChatsSize = 0;
    //La cantidad actual de users renderizados hasta el momento
    public static int currentUsersSize = 0;
    //La cantidad actual de messages en un chat x renderizados hasta el momento
    public static int messagesSize = 0;

    public static View chatsHallActionBar = null;
    public static View usersHallActionBar = null;
    public static View chatActionBar = null;
    public static Resources resources;
    public static boolean GetUsersPostAsyncTaskFinish = false;
    public static boolean RefreshChatsHallAsyncTaskFinish = false;
    public static boolean RefreshUsersAsyncTaskFinish = false;
    public static boolean RefreshChatAsyncTaskFinish = false;
    public static boolean SomethingForMePostAsyncTaskFinish = false;

    public static int GetUsersPostAsyncTaskFrec = 50;
    public static int SomethingForMePostAsyncTaskFrec = 50;

    public static boolean GPS_ON = true;
    public static String USER_KEEPED_LOCATION = "";

    private Constants() {}

    public static void setIp(String ip) {
        ipServer = ip;
        logInUrl = "http://" + ipServer +":" + portServer + "/logIn";
        signUpUrl = "http://" + ipServer + ":" + portServer + "/signUp";
        currentChatsUrl = "http://" + ipServer+ ":" +portServer + "/currentChats";
        setConfigUrl = "http://" + ipServer + ":" + portServer + "/setConfig";
        somethingForMeUrl = "http://" + ipServer + ":" + portServer + "/somethingForMe";
        usersUrl = "http://" + ipServer + ":" + portServer + "/users";
        sendMessageUrl = "http://" + ipServer + ":" + portServer + "/sendMessage";
        deleteChatUrl = "http://" + ipServer + ":" + portServer + "/deleteChat";
        broadcastUrl = "http://" + ipServer + ":" + portServer + "/broadcast";
    }

    public static void initialize(SharedPreferences mSharedPref) {

        String username = mSharedPref.getString(PREF_NAME, "");
        String password = mSharedPref.getString(PREF_PASS, "");
        Constants.user = new User(username, password);
        Constants.user.status = mSharedPref.getString(username+"status", "");
        Constants.user.location = mSharedPref.getString(username+"location", "");
        Constants.user.profile_picture = stringToBitmap(mSharedPref.getString(username + "profile_picture", ""));

        setIp(mSharedPref.getString("ipServer", ""));
        if (Constants.server != null) {
            Constants.server.setSharedPref(mSharedPref);
        }

        Constants.GPS_ON = Boolean.getBoolean(mSharedPref.getString(Constants.user.username+"GPS", ""));

        try {

            JSONObject chatsObject = new JSONObject(mSharedPref.getString(username+"chats", ""));
            JSONArray chats = (JSONArray) chatsObject.get("chats");

            for (int chat = 0; chat < chats.length(); chat++) {
                Constants.user.chats.add(Chat.toChat((org.json.JSONObject) chats.get(chat)));
            }
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
        deleteOk = "";

        chatListView = null;
        chatsAdapter = null;
        usersListView = null;
        usersScroll = null;

        currentChatsSize = 0;
        //La cantidad actual de users renderizados hasta el momento
        currentUsersSize = 0;
        //La cantidad actual de messages en un chat x renderizados hasta el momento
        messagesSize = 0;

        otherUsers.clear();

    }

}
