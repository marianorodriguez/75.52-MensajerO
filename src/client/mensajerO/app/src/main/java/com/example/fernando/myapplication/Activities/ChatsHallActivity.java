package com.example.fernando.myapplication.Activities;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Pair;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.R;
import com.example.fernando.myapplication.Threads.GetUsersPostAsyncTask;
import com.example.fernando.myapplication.Threads.RefreshChatsHallAsyncTask;
import com.example.fernando.myapplication.Threads.SomethingForMePostAsyncTask;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * Created by fernando on 10/04/15.
 */
public class ChatsHallActivity extends ActionBarActivity implements View.OnClickListener {

    public static SomethingForMePostAsyncTask somethingForMePost;
    public static GetUsersPostAsyncTask usersPost;
    public static RefreshChatsHallAsyncTask refreshChats;
    String package_;

    // EL SERVER YA TIENE LOS CHATS ! TIENE LOS CHATS QUE YO TENGO EN EL TELEFONO
    // MANDAR POST CUANDO BORRO UN CHAT ! -----------------------------------------

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.chatshall);

        setTitle("CHATS");

//        Constants.mSharedPreferences = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);
//        SharedPreferences.Editor e = Constants.mSharedPreferences.edit();
//        e.clear();
//        e.commit();

        Constants.mSharedPreferences = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);

        if (Constants.mSharedPreferences.getString(Constants.PREF_NAME, "").isEmpty() ||
                Constants.server.loguedUsers.size() == 0) {

            Constants.mSharedPreferences = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);
            SharedPreferences.Editor e = Constants.mSharedPreferences.edit();
            e.clear();
            e.commit();

            Intent getIn = new Intent(this, GetInActivity.class);
            startActivity(getIn);
            finish();

        } else {
            // cuando queda guardada la sesion e inicia en CHATS
            if (Constants.user == null)
                Constants.initialize();

            somethingForMePost = new SomethingForMePostAsyncTask();
            refreshChats = new RefreshChatsHallAsyncTask();
            usersPost = new GetUsersPostAsyncTask();

            //dibujar los chats que vienen de login en Constants.user.chat
            drawCurrentChats();

            Toast.makeText(this, "Welcome, " + Constants.user.username + "!", Toast.LENGTH_LONG).show();

            package_ = Constants.packager.wrap("somethingForMe", Constants.user);

            somethingForMePost.execute(new Pair<Context, String>(this, package_),
                    new Pair<Context, String>(this, Constants.somethingForMeUrl),
                    new Pair<Context, String>(this, "post"));


            usersPost.execute(new Pair<Context, String>(this, package_),
                    new Pair<Context, String>(this, Constants.usersUrl),
                    new Pair<Context, String>(this, "post"));

            // tirar un hilo que llame a users, que tire todos los usuarios del sistema y cargarlos en constants.users
            // loopea, se hace constantemente. el server manda todos los users

            refreshChats.execute(new Pair<Context, String>(this, package_),
                    new Pair<Context, String>(this, Constants.usersUrl),
                    new Pair<Context, String>(this, "post"));
//            hilo que ve si hay chats nuevos en la lista de chats y si los hay
//            o si hay mensajes nuevo los muestre y los ordene

        }

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.chatshall_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();

        if (id == R.id.users) {

            Intent users = new Intent(this, UsersActivity.class);
            startActivity(users);
            return true;

        } else if (id == R.id.logOut) {

            Constants.mSharedPreferences = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);
            SharedPreferences.Editor e = Constants.mSharedPreferences.edit();

            String username = Constants.mSharedPreferences.getString(Constants.PREF_NAME, "");
            e.putString(username+"chats", Constants.user.chatsToJson().toString());
            // TAMBIEN GUARDAR LA CONFIGURACION
//            e.putString(username+"config", Constants.user.toJsonForDisk());

            e.putString(Constants.PREF_NAME, "");
            e.putString(Constants.PREF_PASS, "");

            e.commit();

            Constants.logInOk = "";
            Constants.currentChatsOk = "";
            Constants.currentChatsSize = 0;
//            Constants.currentChatsSize = 0;
            Constants.chatListView = null;
            Constants.chatsAdapter = null;
            Constants.usersListView = null;
            Constants.usersAdapter = null;
            Constants.otherUsers.clear();

            Intent login = new Intent(this, LogInActivity.class);
            startActivity(login);
            finish();
            return true;

        } else if (id == R.id.settings) {

            Intent config = new Intent(this, ConfigurationActivity.class);
            startActivity(config);
            return true;

        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        if (somethingForMePost != null) {
            somethingForMePost.cancel(true);
            usersPost.cancel(true);
            refreshChats.cancel(true);
        }

        // GUARDAR CHATS en sharedPreferences !
        if (Constants.user != null) {
            SharedPreferences.Editor e = Constants.mSharedPreferences.edit();
            e.putString(Constants.user.username + "chats",
                   Constants.user.chatsToJson().toString());
            e.commit();
        }
    }

    @Override
    public void onClick(View v) {
    }

    public void drawCurrentChats() {

        final ListView listview = (ListView) findViewById(R.id.listview);
        Constants.chatListView = listview;

        ArrayList<String> otherUsersChatingWith = new ArrayList<>();

        for (int chat = 0; chat < Constants.user.chats.size(); chat++) {
            otherUsersChatingWith.add(Constants.user.chats.get(chat).otherUser);
        }

        final StableArrayAdapter adapter = new StableArrayAdapter(this,
                android.R.layout.simple_list_item_1, otherUsersChatingWith);
        listview.setAdapter(adapter);

        Constants.chatsAdapter = adapter;

        listview.setOnItemClickListener(new AdapterView.OnItemClickListener() {

            @Override
            public void onItemClick(AdapterView<?> parent, final View view,
                                    int position, long id) {
                final String chatSelected = (String) parent.getItemAtPosition(position);

                for (int chat = 0; chat < Constants.user.chats.size(); chat++) {
                    if (Constants.user.chats.get(chat).otherUser.compareTo(chatSelected) == 0) {

                        Constants.chatEditor.setChat(Constants.user.chats.get(chat));

                        Constants.chatWith = chatSelected;

                        Intent chat_ = new Intent(getApplicationContext(), ChatActivity.class);
                        startActivity(chat_);
                        break;
                    }
                }

//                adapter.add("Andrea");
//                listview.setAdapter(adapter);
//                                list.remove(item);
//                                adapter.notifyDataSetChanged();
            }
        });
    }

    public class StableArrayAdapter extends ArrayAdapter<String> {

        HashMap<String, Integer> mIdMap = new HashMap<>();

        public StableArrayAdapter(Context context, int textViewResourceId,
                                  ArrayList<String> objects) {
            super(context, textViewResourceId, objects);
            for (int i = 0; i < objects.size(); ++i) {
                mIdMap.put(objects.get(i), i);
            }
        }

        @Override
        public long getItemId(int position) {
            String item = getItem(position);
            return mIdMap.get(item);
        }

        @Override
        public boolean hasStableIds() {
            return true;
        }

        @Override
        public void add(String object) {
            super.add(object);
            mIdMap.size();
            mIdMap.put(object, Constants.user.chats.size());
        }

    }
}

//    private void drawCurrentChats() {
//
//        final ListView listview = (ListView) findViewById(R.id.listview);
//        String[] values = new String[] { "Android", "iPhone", "WindowsMobile",
//                "Blackberry", "WebOS", "Ubuntu", "Windows7", "Max OS X",
//                "Linux", "OS/2", "Ubuntu", "Windows7", "Max OS X", "Linux",
//                "OS/2", "Ubuntu", "Windows7", "Max OS X", "Linux", "OS/2",
//                "Android", "iPhone", "WindowsMobile" };
//
//        final ArrayList<String> list = new ArrayList<>();
//        for (int i = 0; i < values.length; ++i) {
//            list.add(values[i]);
//        }
//        final StableArrayAdapter adapter = new StableArrayAdapter(this,
//                android.R.layout.simple_list_item_1, list);
//        listview.setAdapter(adapter);
//
//        listview.setOnItemClickListener(new AdapterView.OnItemClickListener() {
//
//            @Override
//            public void onItemClick(AdapterView<?> parent, final View view,
//                                    int position, long id) {
//                final String item = (String) parent.getItemAtPosition(position);
//
////                adapter = null;
////                list.add("Andrea");
//
//                adapter.add("Andrea");
//                listview.setAdapter(adapter);
////                adapter.notifyDataSetChanged();
//
////                tirarToast();
////                view.animate().setDuration(2000).alpha(0)
////                        .withEndAction(new Runnable() {
////                            @Override
////                            public void run() {
////                                list.remove(item);
////
////
////                                list.add("Andrea");
////                                StableArrayAdapter adapter2 = new StableArrayAdapter(getApplicationContext(), android.R.layout.simple_list_item_1, list);
////                                listview.setAdapter(adapter2);
//////                                adapter2.notifyDataSetChanged();
////
//////                                adapter.notifyDataSetChanged();
////                                view.setAlpha(1);
////                            }
////                        });
//            }
//
//        });
//    }
//
//private class StableArrayAdapter extends ArrayAdapter<String> {
//
//    HashMap<String, Integer> mIdMap = new HashMap<>();
//
//    public StableArrayAdapter(Context context, int textViewResourceId,
//                              ArrayList<String> objects) {
//        super(context, textViewResourceId, objects);
//        for (int i = 0; i < objects.size(); ++i) {
//            mIdMap.put(objects.get(i), i);
//        }
//    }
//
//    @Override
//    public long getItemId(int position) {
//        String item = getItem(position);
//        return mIdMap.get(item);
//    }
//
//    @Override
//    public boolean hasStableIds() {
//        return true;
//    }
//
//    @Override
//    public void add(String object) {
//        super.add(object);
//        mIdMap.size();
//        //            Toast.makeText(getApplicationContext(),mIdMap.size(), Toast.LENGTH_LONG ).show();
//        mIdMap.put(object, 23);
//    }
//
//}
