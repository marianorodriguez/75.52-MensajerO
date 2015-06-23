package com.fiuba.tallerii.mensajer0.Activities;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Typeface;
import android.os.Bundle;
import android.support.v4.graphics.drawable.RoundedBitmapDrawable;
import android.support.v4.graphics.drawable.RoundedBitmapDrawableFactory;
import android.support.v7.app.ActionBarActivity;
import android.text.InputType;
import android.util.Base64;
import android.util.Pair;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;

import com.fiuba.tallerii.mensajer0.Common.Constants;
import com.fiuba.tallerii.mensajer0.Entities.Chat;
import com.fiuba.tallerii.mensajer0.Entities.User;
import com.example.fernando.mensajerO.R;
import com.fiuba.tallerii.mensajer0.Threads.GetUsersPostAsyncTask;
import com.fiuba.tallerii.mensajer0.Threads.RefreshUsersAsyncTask;
import com.fiuba.tallerii.mensajer0.Threads.SendMessagePostAsyncTask;

/**
 * Created by fernando on 10/04/15.
 */
public class UsersActivity extends ActionBarActivity implements View.OnClickListener {

    public static RefreshUsersAsyncTask refreshUsers;
    public static SendMessagePostAsyncTask sendMessage;
    Context context;
    public static GetUsersPostAsyncTask getUsersPost;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.users);
        context = this;

        getSupportActionBar().setDisplayShowCustomEnabled(true);
        getSupportActionBar().setDisplayShowTitleEnabled(false);

        LayoutInflater inflater = (LayoutInflater) getApplicationContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        View actionBar = inflater.inflate(R.layout.action_bar, null);
        getSupportActionBar().setCustomView(actionBar);

        ((TextView) actionBar.findViewById(R.id.actionBarTitle)).setText("USERS");
        ((TextView) actionBar.findViewById(R.id.actionBarSubtitle)).setText("Status: "+Constants.user.status);

        RoundedBitmapDrawable img;
        img = RoundedBitmapDrawableFactory.create(getResources(), Constants.user.profile_picture);
        img.setCornerRadius(300f);
        ((ImageView) actionBar.findViewById(R.id.actionBarIcon)).setImageDrawable(img);

        Constants.usersHallActionBar = actionBar;

        String package_ = Constants.packager.wrap("somethingForMe", Constants.user);

        Constants.RefreshChatsHallAsyncTaskFinish = true;
        Constants.RefreshUsersAsyncTaskFinish = false;
//        Constants.GetUsersPostAsyncTaskFinish = false;
//        getUsersPost = new GetUsersPostAsyncTask();
//        getUsersPost.execute(new Pair<Context, String>(this, package_),
//                new Pair<Context, String>(this, Constants.usersUrl),
//                new Pair<Context, String>(this, "get"));

        // dibujar los usuarios de la lista de usuarios Constants.users
        drawCurrentUsers();

        refreshUsers = new RefreshUsersAsyncTask();
        refreshUsers.setResources(getResources());
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
            builder.setIcon(R.drawable.broadcastdialog);

            // Set up the input
            final EditText input = new EditText(this);
            // Specify the type of input expected; this, for example, sets the input as a password, and will mask the text
            input.setInputType(InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_WEB_EDIT_TEXT);
            input.setTypeface(Typeface.SANS_SERIF);
            input.setHint("Write your broadcast message here");
            builder.setView(input);

            // Set up the buttons
            builder.setPositiveButton("SEND", new DialogInterface.OnClickListener() {
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
    protected void onResume() {
        super.onResume();

        String package_ = Constants.packager.wrap("somethingForMe", Constants.user);

        Constants.RefreshUsersAsyncTaskFinish = false;
//        Constants.GetUsersPostAsyncTaskFinish = false;
//        getUsersPost = new GetUsersPostAsyncTask();
//        getUsersPost.execute(new Pair<Context, String>(this, package_),
//                new Pair<Context, String>(this, Constants.usersUrl),
//                new Pair<Context, String>(this, "get"));

        refreshUsers = new RefreshUsersAsyncTask();
        refreshUsers.setResources(getResources());
        refreshUsers.execute(new Pair<Context, String>(this, ""),
                new Pair<Context, String>(this, Constants.usersUrl),
                new Pair<Context, String>(this, "post"));

    }

    @Override
    protected void onPause() {
        super.onPause();
//        getUsersPost.cancel(true);
        refreshUsers.cancel(true);
        Constants.RefreshUsersAsyncTaskFinish = true;
//        Constants.GetUsersPostAsyncTaskFinish = true;
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        refreshUsers.cancel(true);
//        getUsersPost.cancel(true);
//        Constants.GetUsersPostAsyncTaskFinish = true;
        Constants.RefreshUsersAsyncTaskFinish = true;
        Constants.RefreshChatsHallAsyncTaskFinish = false;
    }

    private void drawCurrentUsers() {

        Constants.usersScroll = (ScrollView)findViewById(R.id.scroll);

        LinearLayout users = (LinearLayout) Constants.usersScroll.findViewById(R.id.users);
        Constants.usersListView = users;

        RoundedBitmapDrawable img;
        LayoutInflater inflater = (LayoutInflater) getApplicationContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        Constants.currentUsersSize = Constants.otherUsers.size();

        for (int user = 0; user < Constants.otherUsers.size(); user++) {
            User userToShow = Constants.otherUsers.get(user);

            View newUser = inflater.inflate(R.layout.user_item_users, null);

            Bitmap a = userToShow.profile_picture;
            img = RoundedBitmapDrawableFactory.create(getResources(), a);
            img.setCornerRadius(300f);

            ((ImageView) newUser.findViewById(R.id.userItemImage)).setImageDrawable(img);
            ((ImageView) newUser.findViewById(R.id.userItemImage)).setScaleType(ImageView.ScaleType.CENTER_CROP);

            ((TextView) newUser.findViewById(R.id.userItemData)).setText(userToShow.username + "\n" +
                    userToShow.status + " -- "
                    + userToShow.lastTimeConnected
                    + " -- " + userToShow.location);

            newUser.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {

                    boolean hasChat = false;

                    TextView userData = (TextView) v.findViewById(R.id.userItemData);

                    String userSelected = userData.getText().toString().split("\n")[0];

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
            Constants.usersListView.addView(newUser);
        }

        Constants.usersScroll.removeAllViews();
        Constants.usersScroll.addView(Constants.usersListView);

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
