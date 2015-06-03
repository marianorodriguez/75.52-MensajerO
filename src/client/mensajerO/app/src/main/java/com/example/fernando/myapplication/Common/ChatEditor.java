package com.example.fernando.myapplication.Common;

import android.widget.TextView;

import com.example.fernando.myapplication.Entities.Chat;
import com.example.fernando.myapplication.Entities.Message;

import java.util.ArrayList;

/**
 * Created by fernando on 27/04/15.
 */
public class ChatEditor {
    private String owner = Constants.PREF_NAME;
    private String otherUser;
    private Chat chat;
    private TextView chatView;

    public ChatEditor() {}

    public void setChat(TextView chatView) {
        this.chatView = chatView;
    }

    public void renderChat(TextView chatView) {
        this.chatView = chatView;
        Message messageToRender;
        for (int message = 0; message < chat.messages.size(); message++) {

            messageToRender = chat.messages.get(message);

            chatView.append(messageToRender.msg_date);
//            chatView.append(" - " + messageToRender.hour);
            chatView.append(" - " + messageToRender.msg_fromID);
            chatView.append(": " + messageToRender.msg_text + "\n");

        }
    }

    public void renderNewMessages(ArrayList<Message> newMessages) {
        Message messageToRender;
        for (int message = 0; message < newMessages.size(); message++) {

            messageToRender = newMessages.get(message);

            chatView.append(messageToRender.msg_date);
//            chatView.append(" - " + messageToRender.hour);
            chatView.append(" - " + messageToRender.msg_fromID);
            chatView.append(": " + messageToRender.msg_text + "\n");

//            if (messageToRender.emisor.compareTo(owner) == 0) {
//                chat_.append();
//            } else {
//
//            }
        }
    }

    public void renderNewMessage(Message newMessage) {
        ArrayList<Message> tmp = new ArrayList<>();
        tmp.add(newMessage);
        renderNewMessages(tmp);
    }

    public void setChat(Chat chat) {
        this.chat = chat;
    }

    public Chat getChat() {
        return chat;
    }

}
