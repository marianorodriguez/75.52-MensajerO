package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;
import android.widget.Button;
import android.widget.ScrollView;

import com.example.fernando.myapplication.Activities.ChatActivity;
import com.example.fernando.myapplication.Entities.Chat;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Entities.Message;

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

    public void setScrollDownButton (Button scrollDown, boolean firstTime) {
        this.scrollDown = scrollDown;
        this.firstTime = firstTime;
    }

    @Override
    protected String doInBackground(Pair<Context, Chat>... params) {
        chatToUpdate = params[0].second;
        context = params[0].first;

        newMessages = new ArrayList<>();

//        Constants.messagesSize = chatToUpdate.messages.size();

        try {
            Thread.sleep(100);

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

        if (values[0].compareTo("run again") == 0) {
//            Toast.makeText(context, "new refresh chat", Toast.LENGTH_LONG).show();
            ChatActivity.refreshChat = new RefreshChatAsyncTask();
            ChatActivity.refreshChat.execute(new Pair<>(context, chatToUpdate));

            if (firstTime) {
                scrollDown.callOnClick();
                scrollDown.performClick();
                firstTime = false;
            }
            this.cancel(true);
        } else {
            Constants.chatEditor.renderNewMessages(newMessages);
            newMessages.clear();

        }
    }

}
