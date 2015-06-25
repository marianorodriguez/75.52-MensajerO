package com.fiuba.tallerii.mensajer0.Common;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.ScrollView;
import android.widget.TextView;

import com.fiuba.tallerii.mensajer0.Entities.Chat;
import com.fiuba.tallerii.mensajer0.Entities.Message;
import com.fiuba.tallerii.mensajer0.R;
import java.util.ArrayList;

/**
 * Created by fernando on 27/04/15.
 */
public class ChatEditor {
    private String owner = Constants.PREF_NAME;
    private Chat chat;
    private ScrollView chatView;
    private Context context;
    private ScrollView messagesContainer;

    public ChatEditor() {}

    public void setContext(Context context, String owner, ScrollView messagesContainer) {
        this.context = context;
        this.owner = owner;
        this.messagesContainer = messagesContainer;
    }

    public void setChat(ScrollView chatView) {
        this.chatView = chatView;
    }

    public void renderNewMessages(ArrayList<Message> newMessages) {
        Message messageToRender;

        LinearLayout linearLayout = (LinearLayout) messagesContainer.findViewById(R.id.messages);
        linearLayout.setOrientation(LinearLayout.VERTICAL);
        LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        for (int message = 0; message < newMessages.size(); message++) {

            messageToRender = newMessages.get(message);

            View chatMessage = inflater.inflate(R.layout.chatmessage, null);

            if (messageToRender.msg_fromID.compareTo(owner) == 0) {
                chatMessage.findViewById(R.id.othersMessage).setVisibility(View.INVISIBLE);
                ((TextView)chatMessage.findViewById(R.id.myMessage).findViewById(R.id.myText)).setText(messageToRender.msg_text);
                ((TextView)chatMessage.findViewById(R.id.myMessage).findViewById(R.id.myDateTime)).
                        setText(giveFormatToDate(messageToRender.msg_date, messageToRender.msg_time));
            } else {
                chatMessage.findViewById(R.id.myMessage).setVisibility(View.INVISIBLE);
                ((TextView)chatMessage.findViewById(R.id.othersMessage).findViewById(R.id.othersText)).setText(messageToRender.msg_text);
                ((TextView)chatMessage.findViewById(R.id.othersMessage).findViewById(R.id.othersDateTime)).
                        setText(giveFormatToDate(messageToRender.msg_date, messageToRender.msg_time));
            }

            linearLayout.addView(chatMessage, linearLayout.getChildCount(), new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.FILL_PARENT, RelativeLayout.LayoutParams.WRAP_CONTENT));

        }

        messagesContainer.removeAllViews();
        messagesContainer.addView(linearLayout);

    }

    public String giveFormatToDate(String date, String time) {
        return date + " - " + time;
    }

    public void setChat(Chat chat) {
        this.chat = chat;
    }

    public Chat getChat() {
        return chat;
    }

}
