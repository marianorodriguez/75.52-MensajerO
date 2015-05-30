package com.example.fernando.myapplication.Threads;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Pair;
import android.widget.Toast;

import com.example.fernando.myapplication.Activities.ChatActivity;
import com.example.fernando.myapplication.Activities.ChatsHallActivity;
import com.example.fernando.myapplication.Common.Chat;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Common.Message;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by fernando on 27/04/15.
 */
public class RefreshChatAsyncTask extends AsyncTask<Pair<Context, Chat>, String, String> {

    private Chat chatToUpdate;
    private Context context;
    ArrayList<Message> newMessages;

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
            this.cancel(true);
        } else {
            Constants.chatEditor.renderNewMessages(newMessages);
            newMessages.clear();
        }
    }

}
