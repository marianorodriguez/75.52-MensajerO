package com.fiuba.tallerii.mensajer0.Threads;

import android.content.Context;
import android.content.Intent;
import android.content.res.Resources;
import android.os.AsyncTask;
import android.support.v4.graphics.drawable.RoundedBitmapDrawable;
import android.support.v4.graphics.drawable.RoundedBitmapDrawableFactory;
import android.util.Pair;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.fiuba.tallerii.mensajer0.Activities.ChatActivity;
import com.fiuba.tallerii.mensajer0.Activities.UsersActivity;
import com.fiuba.tallerii.mensajer0.Common.Constants;
import com.fiuba.tallerii.mensajer0.Entities.Chat;
import com.fiuba.tallerii.mensajer0.Entities.User;
import com.fiuba.tallerii.mensajer0.R;

import java.util.ArrayList;

/**
 * Created by fernando on 27/04/15.
 */
public class RefreshUsersAsyncTask extends AsyncTask<Pair<Context, String>, String, String> {

    private Context context;
    private Resources resources;

    public void setResources(Resources resources) {
        this.resources = resources;
    }

    @Override
    protected String doInBackground(Pair<Context, String>... params) {

        context = params[0].first;
        try {
            Thread.sleep(1000);

            if (Constants.RefreshUsersAsyncTaskFinish) return null;

            publishProgress("updateUsers");

            publishProgress("run again", params[0].second,
                    params[1].second, params[2].second);

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    protected void onProgressUpdate(String... values) {
        super.onProgressUpdate(values);

        if (values[0].compareTo("run again") == 0) {
            UsersActivity.refreshUsers = new RefreshUsersAsyncTask();
            UsersActivity.refreshUsers.execute(new Pair<>(context, values[1]),
                    new Pair<>(context, values[2]),
                    new Pair<>(context, values[3]));
            this.cancel(true);

        } else {

            int actualUsersSize = Constants.usersListView.getChildCount();
            ArrayList<String> ids = new ArrayList<>();
            ArrayList<Integer> deleted = new ArrayList<>();
            RoundedBitmapDrawable img = null;

            for (int actualUser = 0; actualUser < actualUsersSize; actualUser++) {
                String username = ((TextView) Constants.usersListView.getChildAt(actualUser).
                        findViewById(R.id.userItemData)).getText().toString().split("\n")[0];
                ids.add(username);
                User wanted = isInOtherUsers(username);
                if (wanted != null) {
                    refreshCurrentData(Constants.usersListView.getChildAt(actualUser), wanted, img);
                } else {
                    deleted.add(actualUser);
                }
            }

            for (int userDeleted = 0; userDeleted < deleted.size(); userDeleted++) {
                Constants.usersListView.removeView(Constants.usersListView.
                        getChildAt(deleted.get(userDeleted)));
            }

            LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);

            for (int otherUser = 0; otherUser < Constants.otherUsers.size(); otherUser++) {
                if (!ids.contains(Constants.otherUsers.get(otherUser).username)) {
                    addNewOtherUser(inflater, Constants.otherUsers.get(otherUser));
                }
            }
        }
    }

    private void refreshCurrentData(View user, User wanted, RoundedBitmapDrawable img) {

        ((ImageView)user.findViewById(R.id.userItemImage)).setImageBitmap(wanted.profile_picture);

        ((TextView) user.findViewById(R.id.userItemData)).setText(wanted.username);
        ((TextView) user.findViewById(R.id.userItemStatus)).setText(wanted.status);
        ((TextView) user.findViewById(R.id.userItemLastTime)).setText(wanted.lastTimeConnected);

        if (wanted.location.compareTo("unknown") != 0) {
            user.findViewById(R.id.userItemLocation).setVisibility(View.VISIBLE);
            ((TextView) user.findViewById(R.id.userItemLocation)).setText(wanted.location);
        } else {
            user.findViewById(R.id.userItemLocation).setVisibility(View.INVISIBLE);
        }

    }

    private User isInOtherUsers(String username) {

        for (int otherUser = 0; otherUser < Constants.otherUsers.size(); otherUser++) {
            if (Constants.otherUsers.get(otherUser).username.compareTo(username) == 0) {
                return Constants.otherUsers.get(otherUser);
            }
        }
        return null;
    }

    private void addNewOtherUser(LayoutInflater inflater, User userToShow) {

        View newUser = inflater.inflate(R.layout.user_item_users, null);

        ((ImageView)newUser.findViewById(R.id.userItemImage)).setImageBitmap(userToShow.profile_picture);

        ((TextView) newUser.findViewById(R.id.userItemData)).setText(userToShow.username);
        ((TextView) newUser.findViewById(R.id.userItemStatus)).setText(userToShow.status);
        ((TextView) newUser.findViewById(R.id.userItemLastTime)).setText(userToShow.lastTimeConnected);

        if (userToShow.location.compareTo("unknown") != 0) {
            newUser.findViewById(R.id.userItemLocation).setVisibility(View.VISIBLE);
            ((TextView) newUser.findViewById(R.id.userItemLocation)).setText(userToShow.location);
        } else {
            newUser.findViewById(R.id.userItemLocation).setVisibility(View.INVISIBLE);
        }

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

                        Intent chat_ = new Intent(context, ChatActivity.class);
                        context.startActivity(chat_);
                        break;
                    }
                }
                if (!hasChat) {
                    Chat newChat = new Chat(userSelected);
                    Constants.user.chats.add(newChat);

                    Constants.chatEditor.setChat(newChat);

                    Intent chat_ = new Intent(context, ChatActivity.class);
                    context.startActivity(chat_);
                }
            }
        });

        Constants.usersListView.addView(newUser);

        Constants.usersScroll.removeAllViews();
        Constants.usersScroll.addView(Constants.usersListView);
    }

}
