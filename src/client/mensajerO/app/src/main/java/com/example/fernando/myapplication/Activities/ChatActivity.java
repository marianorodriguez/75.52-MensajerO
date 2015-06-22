package com.example.fernando.myapplication.Activities;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.v4.graphics.drawable.RoundedBitmapDrawable;
import android.support.v4.graphics.drawable.RoundedBitmapDrawableFactory;
import android.support.v7.app.ActionBarActivity;
import android.util.Pair;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.ScrollView;
import android.widget.TextView;

import com.example.fernando.myapplication.Entities.Chat;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Entities.Message;
import com.example.fernando.myapplication.Threads.RefreshChatAsyncTask;
import com.example.fernando.myapplication.R;
import com.example.fernando.myapplication.Threads.SendMessagePostAsyncTask;

import java.util.Calendar;
import java.util.Date;

/**
 * Created by fernando on 10/04/15.
 */
public class ChatActivity extends ActionBarActivity implements View.OnClickListener {

    public static RefreshChatAsyncTask refreshChat;
    public static SendMessagePostAsyncTask sendMessage;
    private Calendar calendar = Calendar.getInstance();
    private ScrollView scroll;

    String otherUserStatus = null;
    Bitmap otherUserPicture = null;
    String otherUserLastTimeConnected = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.chat);

        getSupportActionBar().setDisplayShowCustomEnabled(true);
        getSupportActionBar().setDisplayShowTitleEnabled(false);

        LayoutInflater inflater = (LayoutInflater) getApplicationContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        View actionBar = inflater.inflate(R.layout.action_bar, null);
        getSupportActionBar().setCustomView(actionBar);

        findOtherUserData();

        ((TextView) actionBar.findViewById(R.id.actionBarTitle)).setText("CHAT WITH ".concat(Constants.chatWith));
        if (otherUserStatus.compareTo("offline") != 0) {
            ((TextView) actionBar.findViewById(R.id.actionBarSubtitle)).setText("Status: " + otherUserStatus +
                    "\nLast time seen: " + otherUserLastTimeConnected);
            ((TextView) actionBar.findViewById(R.id.actionBarSubtitle)).setTextSize(10);
        } else {
            ((TextView) actionBar.findViewById(R.id.actionBarSubtitle)).setText("Status: " + otherUserStatus);
        }

        RoundedBitmapDrawable img;
        img = RoundedBitmapDrawableFactory.create(getResources(), otherUserPicture);
        img.setCornerRadius(300f);
        ((ImageView) actionBar.findViewById(R.id.actionBarIcon)).setImageDrawable(img);

        Constants.chatActionBar = actionBar;
        Constants.resources = getResources();

        Button sendButton = (Button) findViewById(R.id.sendButton);
        sendButton.setOnClickListener(this);
        Button focusDownButton = (Button) findViewById(R.id.focusdown);
        focusDownButton.setOnClickListener(this);

        findViewById(R.id.editText).bringToFront();

        sendMessage = new SendMessagePostAsyncTask();
        refreshChat = new RefreshChatAsyncTask();

        Constants.messagesSize = 0;
        scroll = (ScrollView) findViewById(R.id.scrollView);
        refreshChat.setScrollDownButton(focusDownButton, true);
        Constants.chatEditor.setContext(this, Constants.user.username, scroll );
        refreshChat.execute(new Pair<Context, Chat>(this, Constants.chatEditor.getChat()));
        // tirar hilo que se fije si de en la lista de chats hay cambios con este user y actualice la vista

        scroll.fullScroll(ScrollView.FOCUS_DOWN);
    }

    private void findOtherUserData() {
        for (int otherUser = 0; otherUser < Constants.otherUsers.size(); otherUser++) {
            if (Constants.otherUsers.get(otherUser).username.compareTo(Constants.chatWith) == 0) {
                otherUserStatus = Constants.otherUsers.get(otherUser).status;
                otherUserPicture = Constants.otherUsers.get(otherUser).profile_picture;
                otherUserLastTimeConnected = Constants.otherUsers.get(otherUser).lastTimeConnected;
                return;
            }
        }
        otherUserStatus = "offline";
        otherUserPicture = BitmapFactory.decodeResource(this.getResources(),
                R.drawable.offline1);
        otherUserLastTimeConnected = "";
    }

    @Override
    public void onClick(View v) {

        if (v.getId() == R.id.sendButton) {

            EditText edTxt = (EditText) findViewById(R.id.editText);
            String message = edTxt.getText().toString();

            String package_ = Constants.packager.wrap("sendMessage",
                    Constants.user, Constants.chatWith, message);


            Constants.chatEditor.setContext(this, Constants.user.username, scroll);

            sendMessage.execute(new Pair<Context, String>(this, package_),
                    new Pair<Context, String>(this, Constants.sendMessageUrl),
                    new Pair<Context, String>(this, "post"));

            while (Constants.sendMessageOk.compareTo("") == 0) {
                try {
                    Thread.sleep(1);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }

            if (Constants.sendMessageOk.contains("Error")) {}

            if (Constants.sendMessageOk.compareTo("true") == 0) {
                edTxt.setText("");
                Message newMessage = new Message(
                        Constants.user.username,
                        Constants.chatWith,
                        message,
                        getDate(calendar.getTime()),
                        getTime(calendar.getTime()));
                Constants.chatEditor.setContext(this, Constants.user.username, scroll);
                refreshChat.setScrollDownButton((Button)findViewById(R.id.focusdown), true);
                Constants.chatEditor.getChat().messages.add(newMessage);
//                Constants.chatEditor.renderNewMessage(newMessage);
            }

//            Constants.sendMessageOk = "";
            sendMessage = new SendMessagePostAsyncTask();

            scroll.fullScroll(ScrollView.FOCUS_DOWN);

        } else if (v.getId() == R.id.focusdown) {
            scroll.fullScroll(ScrollView.FOCUS_DOWN);
        }
    }

    private String getDate(Date todaysDate) {
        String year = (String) android.text.format.DateFormat.format("yyyy", todaysDate);
        String intMonth = (String) android.text.format.DateFormat.format("MM", todaysDate);
        String day = (String) android.text.format.DateFormat.format("dd", todaysDate);

        return day+"/"+intMonth+ "/"+year;
    }

    private String getTime(Date todaysDate) {
        String min = (String) android.text.format.DateFormat.format("mm", todaysDate);

        String[] parts = todaysDate.toString().split(" ");
        String[] parts2 = parts[3].split(":");
        String hour = parts2[0];

        return hour +":"+min;
    }



    @Override
    protected void onDestroy() {
        super.onDestroy();
        Constants.messagesSize = 0;
        refreshChat.cancel(true);
    }
}
