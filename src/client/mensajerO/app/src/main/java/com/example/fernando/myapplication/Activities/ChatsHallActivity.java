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
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;

import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Threads.GetUsersAsyncTask;
import com.example.fernando.myapplication.Threads.RefreshChatsHallAsyncTask;
import com.example.fernando.myapplication.Threads.ServletPostAsyncTask;
import com.example.fernando.myapplication.Common.User;
import com.example.fernando.myapplication.R;
import com.example.fernando.myapplication.Threads.SomethingForMeAsyncTask;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * Created by fernando on 10/04/15.
 */
public class ChatsHallActivity extends ActionBarActivity implements View.OnClickListener {

    SomethingForMeAsyncTask somethingForMePost;
    GetUsersAsyncTask usersPost;
    RefreshChatsHallAsyncTask refreshChats;
    public String something;
    String package_;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.chatshall);

        Constants.mSharedPreferences = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);

        if (Constants.mSharedPreferences.getString(Constants.PREF_NAME, "").isEmpty()) {

            Intent getIn = new Intent(this, GetInActivity.class);
            startActivity(getIn);
            finish();

        } else {

            Button button2 = (Button) findViewById(R.id.button2);
            button2.setOnClickListener(this);

            somethingForMePost = new SomethingForMeAsyncTask();
            something = "";
            refreshChats = new RefreshChatsHallAsyncTask();
            usersPost = new GetUsersAsyncTask();

            //dibujar los chats que vienen de login en Constansts.user.chat
            drawCurrentChats();

            String username = Constants.mSharedPreferences.getString(Constants.PREF_NAME, "");
            String password = Constants.mSharedPreferences.getString(Constants.PREF_PASS, "");
            Toast.makeText(getApplicationContext(), "Welcome, " + username + "!", Toast.LENGTH_LONG).show();

            User currentUser = new User(username, password);

            package_ = Constants.packager.wrap("somethingForMe", currentUser);

            somethingForMePost.execute(new Pair<Context, String>(this, package_),
                    new Pair<Context, String>(this, Constants.somethingForMeUrl),
                    new Pair<Context, String>(this, "post"));


            usersPost.execute(new Pair<Context, String>(this, package_),
                    new Pair<Context, String>(this, Constants.usersUrl),
                    new Pair<Context, String>(this, "post"));
            // tirar un hilo que llame a users, que tire todos los usuarios del sistema y cargarlos en constants.users
            // loopea, se hace constantemente. el server manda todos los users

            refreshChats.execute();
            // hilo que ve si hay chats nuevos en la lista de chats y si los hay
            // o si hay mensajes nuevo los muestre y los ordene

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
            e.clear();
            e.commit();


            // EL SERVER YA TIENE LOS CHATS ! TIENE LOS CHATS QUE YO TENGO EN EL TELEFONO
            // MANDAR POST CUANDO BORRO UN CHAT !

            Constants.logInOk = "";
            Constants.userChats.clear();

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

        // getResponse
        // GUARDAR CHATS en sharedPreferences !

    }

    @Override
    public void onClick(View v) {

        if (v.getId() == R.id.button2) {

            //setear constante string chatwith para saber q chat mostrar en chat activity

            Intent chat = new Intent(this, ChatActivity.class);
            startActivity(chat);

        }
    }

    private void drawCurrentChats() {

        final ListView listview = (ListView) findViewById(R.id.listview);

        ArrayList<String> otherUsersChatingWith = new ArrayList<>();

        for (int chat = 0; chat < Constants.user.chats.size(); chat++) {
            otherUsersChatingWith.add(Constants.user.chats.get(chat).otherUser);
        }

        final StableArrayAdapter adapter = new StableArrayAdapter(this,
                android.R.layout.simple_list_item_1, otherUsersChatingWith);
        listview.setAdapter(adapter);

        listview.setOnItemClickListener(new AdapterView.OnItemClickListener() {

            @Override
            public void onItemClick(AdapterView<?> parent, final View view,
                                    int position, long id) {
                final String chatSelected = (String) parent.getItemAtPosition(position);

                for (int chat = 0; chat < Constants.user.chats.size(); chat++) {
                    if (Constants.user.chats.get(chat).otherUser.compareTo(chatSelected) == 0) {
                        Constants.chatEditor.setChat(Constants.user.chats.get(chat));

                        Intent chat_ = new Intent(getApplicationContext(), ChatActivity.class);
                        startActivity(chat_);

                    }
                }

//                adapter.add("Andrea");
//                listview.setAdapter(adapter);
//                                list.remove(item);
//                                adapter.notifyDataSetChanged();
            }
        });
    }

    private class StableArrayAdapter extends ArrayAdapter<String> {

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
