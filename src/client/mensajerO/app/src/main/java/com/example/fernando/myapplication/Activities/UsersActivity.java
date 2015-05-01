package com.example.fernando.myapplication.Activities;

import android.content.Context;
import android.content.Intent;
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

import com.example.fernando.myapplication.Common.Chat;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Mocks.Mocks;
import com.example.fernando.myapplication.Threads.RefreshUsersAsyncTask;
import com.example.fernando.myapplication.R;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * Created by fernando on 10/04/15.
 */
public class UsersActivity extends ActionBarActivity implements View.OnClickListener {

    RefreshUsersAsyncTask refreshUsers;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.users);

        if (Constants.otherUsers.size() == 0) {
            Mocks.createFakeUsers();
            Constants.otherUsers = Mocks.otherUsers;
        }

        // dibujar los usuarios de la lista de usuarios Constants.users
        drawCurrentUsers();

        refreshUsers = new RefreshUsersAsyncTask();
        refreshUsers.execute();
        // tirar hilo que compruebe si hay nuevos usuarios y los dibuje

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.users_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent login in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.chatsHall) {

            finish();
            return true;

        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    public void onClick(View v) {
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        refreshUsers.cancel(true);
    }

    private void drawCurrentUsers(){

        final ListView listview = (ListView) findViewById(R.id.listview);

        Constants.usersListView = listview;

        ArrayList<String> users = new ArrayList<>();

        for (int user = 0; user < Constants.otherUsers.size(); user++) {
            users.add(Constants.otherUsers.get(user).username);
        }

        final StableArrayAdapter adapter = new StableArrayAdapter(this,
                android.R.layout.simple_list_item_1, users);
        listview.setAdapter(adapter);

        Constants.usersAdapter = adapter;

        listview.setOnItemClickListener(new AdapterView.OnItemClickListener() {

            @Override
            public void onItemClick(AdapterView<?> parent, final View view,
                                    int position, long id) {

                final String userSelected = (String) parent.getItemAtPosition(position);
                boolean hasChat = false;

                Constants.chatWith = userSelected;

                for (int chat = 0; chat < Constants.user.chats.size(); chat++) {
                    if (Constants.user.chats.get(chat).otherUser.compareTo(userSelected) == 0) {
                        hasChat = true;

                        Constants.chatEditor.setChat(Constants.user.chats.get(chat));

                        Intent chat_ = new Intent(getApplicationContext(), ChatActivity.class);
                        startActivity(chat_);
                        break;
                    }
                }
                if (!hasChat) {
                    Chat newChat = new Chat(userSelected);
                    Constants.user.chats.add(newChat);

                    Constants.chatEditor.setChat(newChat);

                    Intent chat_ = new Intent(getApplicationContext(), ChatActivity.class);
                    startActivity(chat_);

                }
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
            //            Toast.makeText(getApplicationContext(),mIdMap.size(), Toast.LENGTH_LONG ).show();
            mIdMap.put(object, 23);
        }

    }

}
