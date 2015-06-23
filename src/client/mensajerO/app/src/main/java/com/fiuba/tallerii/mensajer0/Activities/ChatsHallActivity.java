package com.fiuba.tallerii.mensajer0.Activities;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.support.v4.graphics.drawable.RoundedBitmapDrawable;
import android.support.v4.graphics.drawable.RoundedBitmapDrawableFactory;
import android.support.v7.app.ActionBarActivity;
import android.util.Base64;
import android.util.Pair;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.fiuba.tallerii.mensajer0.Common.Constants;
import com.example.fernando.mensajerO.R;
import com.fiuba.tallerii.mensajer0.Threads.CurrentChatsPostAsyncTask;
import com.fiuba.tallerii.mensajer0.Threads.DeleteChatPostAsyncTask;
import com.fiuba.tallerii.mensajer0.Threads.GetUsersPostAsyncTask;
import com.fiuba.tallerii.mensajer0.Threads.RefreshChatsHallAsyncTask;
import com.fiuba.tallerii.mensajer0.Threads.SomethingForMePostAsyncTask;

import java.io.ByteArrayOutputStream;
import java.util.ArrayList;
import java.util.HashMap;

/**
 * Created by fernando on 10/04/15.
 */
public class ChatsHallActivity extends ActionBarActivity implements View.OnClickListener {

    public static SomethingForMePostAsyncTask somethingForMePost;
    public static GetUsersPostAsyncTask getUsersPost;
    public static RefreshChatsHallAsyncTask refreshChats;
    CurrentChatsPostAsyncTask currentChatsGet;
    public static DeleteChatPostAsyncTask deleteChatPost;
    String package_;
    Context context;

    SharedPreferences mSharedPref;

    // EL SERVER YA TIENE LOS CHATS ! TIENE LOS CHATS QUE YO TENGO EN EL TELEFONO
    // MANDAR POST CUANDO BORRO UN CHAT ! -----------------------------------------

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.chatshall);

        context = this;
//        mSharedPref= getSharedPreferences(Constants.PREFS, MODE_PRIVATE);
//        SharedPreferences.Editor ee = mSharedPref.edit();
//        ee.clear();
//        ee.commit();

        mSharedPref = getSharedPreferences(Constants.PREFS, MODE_PRIVATE);

        if (mSharedPref.getString(Constants.PREF_NAME, "").isEmpty()) {

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
            currentChatsGet = new CurrentChatsPostAsyncTask();
            deleteChatPost = new DeleteChatPostAsyncTask();

            LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            View buttonLayout = inflater.inflate(R.layout.logout, null);

            Button logOutButton = (Button) buttonLayout.findViewById(R.id.logOutButton);
            logOutButton.setOnClickListener(this);

            //dibujar los chats que vienen de login en Constants.user.chats
            drawCurrentChats();

            Toast.makeText(this, "Welcome, " + Constants.user.username + "!", Toast.LENGTH_SHORT).show();

            package_ = Constants.packager.wrap("somethingForMe", Constants.user);


            Constants.RefreshChatsHallAsyncTaskFinish = false;
            Constants.GetUsersPostAsyncTaskFinish = false;
            Constants.SomethingForMePostAsyncTaskFinish = false;
            somethingForMePost.execute(new Pair<Context, String>(this, package_),
                    new Pair<Context, String>(this, Constants.somethingForMeUrl),
                    new Pair<Context, String>(this, "get"));

            getUsersPost.execute(new Pair<Context, String>(this, package_),
                    new Pair<Context, String>(this, Constants.usersUrl),
                    new Pair<Context, String>(this, "get"));


            currentChatsGet.execute(new Pair<Context, String>(this, package_),
                    new Pair<Context, String>(this, Constants.currentChatsUrl),
                    new Pair<Context, String>(this, "get"));

            int timeout = 0;
            while (Constants.currentChatsOk.isEmpty()) {
                try {
                    Thread.sleep(1000);
                    timeout++;
                    if (timeout == 4)
                        Constants.currentChatsOk = "Error";
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }

            if (Constants.currentChatsOk.contains("Error")) {
                Toast.makeText(this, "Couldn't connect with server.", Toast.LENGTH_LONG).show();
                Constants.currentChatsOk = "";

                Constants.RefreshChatsHallAsyncTaskFinish = true;
                Constants.GetUsersPostAsyncTaskFinish = true;
                Constants.SomethingForMePostAsyncTaskFinish = true;
                Constants.RefreshUsersAsyncTaskFinish = true;

                sayGodbye();

            }

            Constants.currentChatsSize = 0;

            refreshChats.execute(new Pair<Context, String>(this, package_),
                    new Pair<Context, String>(this, Constants.usersUrl),
                    new Pair<Context, String>(this, "post"));

            getSupportActionBar().setDisplayShowCustomEnabled(true);
            getSupportActionBar().setDisplayShowTitleEnabled(false);

//            LayoutInflater inflater = (LayoutInflater) getApplicationContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            View actionBar = inflater.inflate(R.layout.action_bar, null);
            getSupportActionBar().setCustomView(actionBar);

            ((TextView) actionBar.findViewById(R.id.actionBarTitle)).setText("CHATS HALL");
            ((TextView) actionBar.findViewById(R.id.actionBarSubtitle)).setText("Status: "+Constants.user.status);

            RoundedBitmapDrawable img;
            img = RoundedBitmapDrawableFactory.create(getResources(), Constants.user.profile_picture);
            img.setCornerRadius(300f);
            ((ImageView) actionBar.findViewById(R.id.actionBarIcon)).setImageDrawable(img);

            Constants.chatsHallActionBar = actionBar;

        }
    }

    public String BitMapToString(Bitmap bitmap){

        ByteArrayOutputStream baos=new  ByteArrayOutputStream();
        bitmap.compress(Bitmap.CompressFormat.PNG, 100, baos);
        byte [] b=baos.toByteArray();
        String temp=Base64.encodeToString(b, Base64.DEFAULT);
        temp = temp.replaceAll("(?:\\r\\n|\\n\\r|\\n|\\r)", "");
        return temp;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.chatshall_menu, menu);
        return true;
    }

    @Override
    protected void onResume() {
        super.onResume();
        refreshChats = new RefreshChatsHallAsyncTask();
        refreshChats.execute(new Pair<Context, String>(this, package_),
                new Pair<Context, String>(this, Constants.usersUrl),
                new Pair<Context, String>(this, "post"));
    }

    @Override
    protected void onPause() {
        super.onPause();
        refreshChats.cancel(true);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();

        if (id == R.id.users) {

            Intent users = new Intent(this, UsersActivity.class);
            startActivity(users);
            return true;

        } else if (id == R.id.logOut) {

            sayGodbye();

        } else if (id == R.id.settings) {

            Intent config = new Intent(this, ConfigurationActivity.class);
            startActivity(config);
            return true;

        }

        return super.onOptionsItemSelected(item);
    }

    public void sayGodbye(View v) {
        SharedPreferences.Editor e = mSharedPref.edit();

        String username = mSharedPref.getString(Constants.PREF_NAME, "");
        e.putString(username+"chats", Constants.user.chatsToJson().toString());

        e.putString(Constants.PREF_NAME, "");
        e.putString(Constants.PREF_PASS, "");

        e.commit();

        Intent login = new Intent(this, LogInActivity.class);
        startActivity(login);
        finish();
    }

    public void sayGodbye() {
        SharedPreferences.Editor e = mSharedPref.edit();

        String username = mSharedPref.getString(Constants.PREF_NAME, "");
        e.putString(username+"chats", Constants.user.chatsToJson().toString());

        e.putString(Constants.PREF_NAME, "");
        e.putString(Constants.PREF_PASS, "");

        e.commit();

        Intent login = new Intent(this, LogInActivity.class);
        startActivity(login);
        finish();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        if (somethingForMePost != null) {
            somethingForMePost.cancel(true);
            getUsersPost.cancel(true);
            refreshChats.cancel(true);

            Constants.RefreshChatsHallAsyncTaskFinish = true;
            Constants.GetUsersPostAsyncTaskFinish = true;
            Constants.SomethingForMePostAsyncTaskFinish = true;
            Constants.RefreshUsersAsyncTaskFinish = true;
        }

        // GUARDAR CHATS en sharedPreferences !
        if (Constants.user != null) {
            SharedPreferences.Editor e = mSharedPref.edit();
            e.putString(Constants.user.username + "chats", Constants.user.chatsToJson().toString());
            e.putString(Constants.user.username + "profile_picture", BitMapToString(Constants.user.profile_picture));
            e.putString(Constants.user.username + "status", Constants.user.status);
            e.commit();
        }

        Constants.reset();
    }

    @Override
    public void onClick(View v) {
        if (v.getId() == R.id.logOutButton) {
            sayGodbye();
        }
    }

    public void drawCurrentChats() {

        final ListView listview = (ListView) findViewById(R.id.listview);
        Constants.chatListView = listview;

        ArrayList<String> otherUsersChatingWith = new ArrayList<>();

        Constants.currentChatsSize = 0;

        final StableArrayAdapter adapter = new StableArrayAdapter(this,
                R.layout.user_item_chats, R.id.userItemData, otherUsersChatingWith);
        listview.setAdapter(adapter);

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
            }
        });

        listview.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {

            public boolean onItemLongClick(final AdapterView<?> parent, View v,
                                           final int position, long id) {

                AlertDialog.Builder deleteChat = new AlertDialog.Builder(context);
                deleteChat.setTitle("Delete entry");
                deleteChat.setMessage("Are you sure you want to delete this entry?");
                deleteChat.setPositiveButton(android.R.string.yes, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {

                        final String chatSelected = (String) parent.getItemAtPosition(position);
                        doDeleteOfChat(chatSelected);
                    }
                });
                deleteChat.setNegativeButton(android.R.string.no, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {
                        // do nothing
                    }
                });
                deleteChat.setIcon(android.R.drawable.ic_delete);
                deleteChat.show();
                return true;
            }
        });
    }

    private void doDeleteOfChat(String chatSelected) {
        String package_ = Constants.packager.wrap("deleteChat", Constants.user, chatSelected, "");
        deleteChatPost.execute(new Pair<Context, String>(this, package_),
                new Pair<Context, String>(this, Constants.deleteChatUrl),
                new Pair<Context, String>(this, "post"));

        Constants.deleteOk = "true";
        while (Constants.deleteOk.compareTo("") == 0) {
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        if (Constants.deleteOk.contains("Error")) {}

        if (Constants.deleteOk.compareTo("true") == 0) {

            // borrar el chat de COnstants.user.chats
            for (int chat = 0; chat < Constants.user.chats.size(); chat++) {
                if (Constants.user.chats.get(chat).otherUser.compareTo(chatSelected) == 0) {
                    Constants.user.chats.remove(chat);
                }
            }
        } else {

            Toast.makeText(this, "Couldn't delete the selected chat.", Toast.LENGTH_SHORT).show();
        }
        deleteChatPost = new DeleteChatPostAsyncTask();
        Constants.deleteOk = "";

    }

    public class StableArrayAdapter extends ArrayAdapter<String> {
        // hashmap <User, integer>
        HashMap<String, Integer> mIdMap = new HashMap<>();

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

            mIdMap.put(object, Constants.user.chats.size());
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            View userView = super.getView(position, convertView, parent);

            TextView userItemData = (TextView) userView.findViewById(R.id.userItemData);
            ImageView userItemImage = (ImageView) userView.findViewById(R.id.userItemImage);

            RoundedBitmapDrawable img;
//            RoundedBitmapDrawable img; = RoundedBitmapDrawableFactory.create(getResources(), bitmap);
//            img.setCornerRadius(radius);
//
//            imageView.setImageDrawable(img);
            String username = userItemData.getText().toString().split("\n")[0];
            for (int otherUser = 0; otherUser < Constants.otherUsers.size(); otherUser++) {
                if (Constants.otherUsers.get(otherUser).username.compareTo(username) == 0) {

                    Bitmap a = Constants.otherUsers.get(otherUser).profile_picture;
                    img = RoundedBitmapDrawableFactory.create(getResources(), a);
                    img.setCornerRadius(Math.max(a.getWidth(), a.getHeight()) / 2.0f);
                    userItemImage.setImageDrawable(img);

//                    userItemImage.setImageBitmap(Constants.otherUsers.get(otherUser).profile_picture);
                    break;
                }
            }
            return userView;
        }

    }
}
