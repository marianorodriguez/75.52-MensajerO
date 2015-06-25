package com.fiuba.tallerii.mensajer0.Threads;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.support.v4.graphics.drawable.RoundedBitmapDrawable;
import android.support.v4.graphics.drawable.RoundedBitmapDrawableFactory;
import android.util.Pair;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ScrollView;
import android.widget.TextView;

import com.fiuba.tallerii.mensajer0.Activities.ChatActivity;
import com.fiuba.tallerii.mensajer0.Entities.Chat;
import com.fiuba.tallerii.mensajer0.Common.Constants;
import com.fiuba.tallerii.mensajer0.Entities.Message;
import com.example.fernando.mensajerO.R;

import java.util.ArrayList;

/**
 * Created by fernando on 27/04/15.
 */
public class RefreshChatAsyncTask extends AsyncTask<Pair<Context, Chat>, String, String> {

    private Chat chatToUpdate;
    private Context context;
    ArrayList<Message> newMessages;
    private Button scrollDown;
    boolean firstTime = false;
    String otherUserStatus = null;
    Bitmap otherUserPicture = null;
    String otherUserLastTimeConnected = null;
    ScrollView scroll = null;

    boolean scrollRequired = false;

    public void setScrollDownButton (Button scrollDown, boolean firstTime, ScrollView cont) {
        this.scroll = cont;
        this.scrollDown = scrollDown;
        this.firstTime = firstTime;
    }

    @Override
    protected String doInBackground(Pair<Context, Chat>... params) {
        chatToUpdate = params[0].second;
        context = params[0].first;

        newMessages = new ArrayList<>();

        try {
            Thread.sleep(100);

            if (Constants.RefreshChatAsyncTaskFinish) return null;

            if (chatToUpdate.messages.size() > Constants.messagesSize) {

                for (int message = Constants.messagesSize;
                     message < chatToUpdate.messages.size();
                     message++) {
                    newMessages.add(chatToUpdate.messages.get(message));
                }
                Constants.messagesSize = chatToUpdate.messages.size();
//                Constants.chatEditor.renderNewMessages(newMessages);
                publishProgress("");
            }

            publishProgress("run again");

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    protected void onProgressUpdate(String... values) {
        super.onProgressUpdate(values);

        findOtherUserData();

        ((TextView) Constants.chatActionBar.findViewById(R.id.actionBarTitle)).setText("CHAT WITH ".concat(Constants.chatWith));
        if (otherUserStatus.compareTo("offline") != 0) {
            ((TextView) Constants.chatActionBar.findViewById(R.id.actionBarSubtitle)).setText("Status: " + otherUserStatus +
                    "\nLast time seen: " + otherUserLastTimeConnected);
            ((TextView) Constants.chatActionBar.findViewById(R.id.actionBarSubtitle)).setTextSize(10);
        } else {
            ((TextView) Constants.chatActionBar.findViewById(R.id.actionBarSubtitle)).setText("Status: " + otherUserStatus);
        }

        RoundedBitmapDrawable img;
        img = RoundedBitmapDrawableFactory.create(Constants.resources, otherUserPicture);
        img.setCornerRadius(300f);
        ((ImageView) Constants.chatActionBar.findViewById(R.id.actionBarIcon)).setImageDrawable(img);

        if (values[0].compareTo("run again") == 0) {
//            Toast.makeText(context, "new refresh chat", Toast.LENGTH_LONG).show();
            ChatActivity.refreshChat = new RefreshChatAsyncTask();
            ChatActivity.refreshChat.execute(new Pair<>(context, chatToUpdate));

            LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            View chat = inflater.inflate(R.layout.chat, null);
            chat.findViewById(R.id.editText).requestFocus();
//            scrollDown = (Button) chat.findViewById(R.id.focusdown);
//            scrollDown.performClick();
//            scrollDown.callOnClick();



            if (firstTime) {
                scrollDown.callOnClick();
                scrollDown.performClick();
                firstTime = false;
            }

            if (scrollRequired)
                chat.findViewById(R.id.editText).callOnClick();
            else {
                scrollRequired = false;
                chat.findViewById(R.id.editText).requestFocus();
            }

        } else {

//            LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
//            View chat = inflater.inflate(R.layout.chat, null);
//            scrollDown = (Button) chat.findViewById(R.id.focusdown);
//
//            scroll = (ScrollView) chat.findViewById(R.id.scrollView);



            Constants.chatEditor.renderNewMessages(newMessages);

            scrollRequired = true;

//            scroll.scrollTo(0, scroll.getBottom());
//            scroll.fullScroll(ScrollView.FOCUS_DOWN);
//            ChatActivity.scrollDown();

            newMessages.clear();

        }
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
        otherUserPicture = BitmapFactory.decodeResource(Constants.resources,
                R.drawable.offline1);
        otherUserLastTimeConnected = "";
    }

}
