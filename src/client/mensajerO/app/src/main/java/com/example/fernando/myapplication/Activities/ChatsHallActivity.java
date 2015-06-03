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
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.R;
import com.example.fernando.myapplication.Threads.DeleteChatPostAsyncTask;
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
    public static GetUsersPostAsyncTask getUsersPost;
    public static RefreshChatsHallAsyncTask refreshChats;
    public static DeleteChatPostAsyncTask deleteChat;
    String package_;

    SharedPreferences mSharedPref;

    // EL SERVER YA TIENE LOS CHATS ! TIENE LOS CHATS QUE YO TENGO EN EL TELEFONO
    // MANDAR POST CUANDO BORRO UN CHAT ! -----------------------------------------

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.chatshall);

        setTitle("CHATS");

//        mSharedPref= getSharedPreferences(Constants.PREFS, MODE_PRIVATE);
//        SharedPreferences.Editor ee = mSharedPref.edit();
//        ee.clear();
//        ee.commit();

        mSharedPref = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);

//        if ((Constants.server != null && Constants.server.loguedUsers.size() == 0) ||
        if (/*(Constants.server != null) ||*/
                mSharedPref.getString(Constants.PREF_NAME, "").isEmpty()) {
//        if (Constants.mSharedPreferences.getString(Constants.PREF_NAME, "").isEmpty() || Constants.server == null ||
//                Constants.server.loguedUsers.size() == 0) {

//            if (Constants.mSharedPreferences.getString(Constants.PREF_NAME, "").isEmpty()) {
//            SharedPreferences.Editor e = mSharedPref.edit();
//            e.clear();
//            e.commit();

            Intent getIn = new Intent(this, GetInActivity.class);
            startActivity(getIn);
            finish();

        } else {
            // cuando queda guardada la sesion e inicia en CHATS
            if (Constants.user == null)
                Constants.initialize(mSharedPref);

            somethingForMePost = new SomethingForMePostAsyncTask();
            refreshChats = new RefreshChatsHallAsyncTask();
            getUsersPost = new GetUsersPostAsyncTask();

            //dibujar los chats que vienen de login en Constants.user.chats
            drawCurrentChats();

            Toast.makeText(this, "Welcome, " + Constants.user.username + "!", Toast.LENGTH_LONG).show();

            package_ = Constants.packager.wrap("somethingForMe", Constants.user);

            somethingForMePost.execute(new Pair<Context, String>(this, package_),
                    new Pair<Context, String>(this, Constants.somethingForMeUrl),
                    new Pair<Context, String>(this, "get"));


            getUsersPost.execute(new Pair<Context, String>(this, package_),
                    new Pair<Context, String>(this, Constants.usersUrl),
                    new Pair<Context, String>(this, "get"));

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

            SharedPreferences.Editor e = mSharedPref.edit();

            String username = mSharedPref.getString(Constants.PREF_NAME, "");
            e.putString(username+"chats", Constants.user.chatsToJson().toString());

            e.putString(Constants.PREF_NAME, "");
            e.putString(Constants.PREF_PASS, "");

            e.commit();

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
            getUsersPost.cancel(true);
            refreshChats.cancel(true);
        }

        // GUARDAR CHATS en sharedPreferences !
        if (Constants.user != null) {
            SharedPreferences.Editor e = mSharedPref.edit();
            e.putString(Constants.user.username + "chats", Constants.user.chatsToJson().toString());
            e.commit();
        }

        Constants.reset();
    }

    @Override
    public void onClick(View v) {
    }

    public void drawCurrentChats() {

        // si Constants.users.chats esta vacia --> tratar de leer de sharedprefs los chats y armar esos.
        //o sea cargar constants.user.chats con los chats de sharedprefs

        final ListView listview = (ListView) findViewById(R.id.listview);
        Constants.chatListView = listview;

        // ESta deberia ser una lista de User, igual Constants.users
        // que saca los users del get users, que hay qe hacerlo antes.
        ArrayList<String> otherUsersChatingWith = new ArrayList<>();

        for (int chat = 0; chat < Constants.user.chats.size(); chat++) {
            otherUsersChatingWith.add(Constants.user.chats.get(chat).otherUser);
        }

        Constants.currentChatsSize = Constants.user.chats.size();

        final StableArrayAdapter adapter = new StableArrayAdapter(this,
                R.layout.user_item, R.id.userItemData, otherUsersChatingWith);
        listview.setAdapter(adapter);

//        final StableArrayAdapter adapter = new StableArrayAdapter(this,
//                android.R.layout.simple_list_item_1 , otherUsersChatingWith);
//        listview.setAdapter(adapter);

        Constants.chatsAdapter = adapter;

        listview.setOnItemClickListener(new AdapterView.OnItemClickListener() {

            @Override
            public void onItemClick(AdapterView<?> parent, final View view,
                                    int position, long id) {
                // ver aca el tema de donde es el touch para qe lo tome y que trae
                // getItemAtposition
                final String chatSelected = (String) parent.getItemAtPosition(position);

                for (int chat = 0; chat < Constants.user.chats.size(); chat++) {
                    if (Constants.user.chats.get(chat).otherUser.compareTo(chatSelected) == 0) {

                        String chatSelected2 = chatSelected.split("\n")[0];

                        Constants.chatEditor.setChat(Constants.user.chats.get(chat));

                        Constants.chatWith = chatSelected2;

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
        // hashmap <User, integer>
        HashMap<String, Integer> mIdMap = new HashMap<>();

        // Aca deberia pasarle un ArrayList<User>
        public StableArrayAdapter(Context context,
                                  int resource,
                                  int textViewResourceId,
                                  ArrayList<String> objects) {
            super(context, resource, textViewResourceId, objects);
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

        // add (User object)
        @Override
        public void add(String object) {
            super.add(object);
            mIdMap.size();
            mIdMap.put(object, Constants.user.chats.size());
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            View userView = super.getView(position, convertView, parent);

            TextView userItemData = (TextView) userView.findViewById(R.id.userItemData);
            ImageView userItemImage = (ImageView) userView.findViewById(R.id.userItemImage);

            String username = userItemData.getText().toString().split("\n")[0];
            for (int otherUser = 0; otherUser < Constants.otherUsers.size(); otherUser++) {
                if (Constants.otherUsers.get(otherUser).username.compareTo(username) == 0) {
                    userItemImage.setImageBitmap(Constants.otherUsers.get(otherUser).profile_picture);
                    break;
                }
            }
            return userView;
        }

    }
}
