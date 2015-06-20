package com.example.fernando.myapplication.Activities;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.text.InputType;
import android.util.Base64;
import android.util.Pair;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.example.fernando.myapplication.Entities.Chat;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Entities.Message;
import com.example.fernando.myapplication.Entities.User;
import com.example.fernando.myapplication.Threads.RefreshUsersAsyncTask;
import com.example.fernando.myapplication.R;
import com.example.fernando.myapplication.Threads.SendMessagePostAsyncTask;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * Created by fernando on 10/04/15.
 */
public class UsersActivity extends ActionBarActivity implements View.OnClickListener {

    public static RefreshUsersAsyncTask refreshUsers;
    public static SendMessagePostAsyncTask sendMessage;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.users);

        // dibujar los usuarios de la lista de usuarios Constants.users
        drawCurrentUsers();

        refreshUsers = new RefreshUsersAsyncTask();
        refreshUsers.execute(new Pair<Context, String>(this, ""),
                new Pair<Context, String>(this, Constants.usersUrl),
                new Pair<Context, String>(this, "post"));
        // tirar hilo que compruebe si hay nuevos usuarios y los dibuje
        sendMessage = new SendMessagePostAsyncTask();
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

        }  else if (id == R.id.broadcast) {

            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setTitle("Send broadcast");
            builder.setIcon(android.R.drawable.ic_dialog_alert);

            // Set up the input
            final EditText input = new EditText(this);
            // Specify the type of input expected; this, for example, sets the input as a password, and will mask the text
            input.setInputType(InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_WEB_EDIT_TEXT);
            builder.setView(input);


            // Set up the buttons
            builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    if (!input.getText().toString().isEmpty()) {
                        sendingBroadcast(input.getText().toString());
                    }
                }
            });
            builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    dialog.cancel();
                }
            });

            builder.show();
        }

        return super.onOptionsItemSelected(item);
    }

    private void sendingBroadcast(String message) {

        String package_ = Constants.packager.wrap("sendMessage",
                Constants.user, "all", message);

        sendMessage.execute(new Pair<Context, String>(this, package_),
                new Pair<Context, String>(this, Constants.broadcastUrl),
                new Pair<Context, String>(this, "post"));

        while (Constants.sendMessageOk.compareTo("") == 0) {
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        if (Constants.sendMessageOk.contains("Error")) {}

        if (Constants.sendMessageOk.compareTo("true") == 0) {
            Toast.makeText(this, "Broadcast message sent.", Toast.LENGTH_LONG).show();
        }

        Constants.sendMessageOk = "";
        sendMessage = new SendMessagePostAsyncTask();
    }

    @Override
    public void onClick(View v) {
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        refreshUsers.cancel(true);
    }

    private void drawCurrentUsers() {

        final ListView listview = (ListView) findViewById(R.id.listview);

        Constants.usersListView = listview;

        ArrayList<String> users = new ArrayList<>();

        for (int user = 0; user < Constants.otherUsers.size(); user++) {
            User userToShow = Constants.otherUsers.get(user);
            users.add(userToShow.username + "\n" +
                    userToShow.status + " - "
                    + userToShow.lastTimeConnected
                    + " - " + userToShow.location);
        }

        Constants.currentUsersSize = Constants.otherUsers.size();

        final StableArrayAdapter adapter = new StableArrayAdapter(this,
                R.layout.user_item, R.id.userItemData, users);
        listview.setAdapter(adapter);

//        final StableArrayAdapter adapter = new StableArrayAdapter(this,
//                android.R.layout.simple_list_item_1, users);
//        listview.setAdapter(adapter);

        Constants.usersAdapter = adapter;

        listview.setOnItemClickListener(new AdapterView.OnItemClickListener() {

            @Override
            public void onItemClick(AdapterView<?> parent, final View view,
                                    int position, long id) {

                final String userSelected = (String) parent.getItemAtPosition(position);
                boolean hasChat = false;

                String userSelected2 = userSelected.split("\n")[0];

                Constants.chatWith = userSelected2;

                for (int chat = 0; chat < Constants.user.chats.size(); chat++) {
                    if (Constants.user.chats.get(chat).otherUser.compareTo(userSelected2) == 0) {
                        hasChat = true;

                        Constants.chatEditor.setChat(Constants.user.chats.get(chat));

                        Intent chat_ = new Intent(getApplicationContext(), ChatActivity.class);
                        startActivity(chat_);
                        break;
                    }
                }
                if (!hasChat) {
                    Chat newChat = new Chat(userSelected2);
                    Constants.user.chats.add(newChat);

                    Constants.chatEditor.setChat(newChat);

                    Intent chat_ = new Intent(getApplicationContext(), ChatActivity.class);
                    startActivity(chat_);

                }
            }

        });
    }

    public class StableArrayAdapter extends ArrayAdapter<String> {

        public HashMap<String, Integer> mIdMap = new HashMap<>();

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
        public void clear() {
            super.clear();
//            mIdMap.clear();
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

            //            Toast.makeText(getApplicationContext(),mIdMap.size(), Toast.LENGTH_LONG ).show();
            mIdMap.put(object, Constants.otherUsers.size());
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

    public Bitmap stringToBitmap(String pictureString){
        try {
            byte [] encodeByte= Base64.decode(pictureString, Base64.DEFAULT);
            Bitmap bitmap= BitmapFactory.decodeByteArray(encodeByte, 0, encodeByte.length);
            return bitmap;
        } catch(Exception e) {
            e.getMessage();
            return null;
        }
    }

}
