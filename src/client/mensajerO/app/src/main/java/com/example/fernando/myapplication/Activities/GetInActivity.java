package com.example.fernando.myapplication.Activities;

import android.content.Context;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Base64;
import android.util.Pair;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.example.fernando.myapplication.Common.ServletPostAsyncTask;
import com.example.fernando.myapplication.R;

import java.io.UnsupportedEncodingException;

public class GetInActivity extends ActionBarActivity implements View.OnClickListener{
    ServletPostAsyncTask post;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.getin);

//        String fer = "hello";
////        System.out.println(fer);
//
//        byte[] data = new byte[0];
//        try {
//            data = fer.getBytes("UTF-8");
//        } catch (UnsupportedEncodingException e) {
//            e.printStackTrace();
//        }
//
//        String fer64 = Base64.encodeToString(data, Base64.NO_WRAP);
//
//        fer64 = fer64.replaceAll("(?:\\r\\n|\\n\\r|\\n|\\r)", "");
//        System.out.println(fer64);
//
////        new ServletPostAsyncTask().execute(new Pair<Context, String>(this, fer64));
//        post = new ServletPostAsyncTask();
//        post.execute(new Pair<Context, String>(this, "Grupo Taller II"),
//                new Pair<Context, String>(this, "http://10.0.2.2:8080/hello"),
//                new Pair<Context, String>(this, "post"));

//        TextView mainTextView = (TextView) findViewById(R.id.textView);
//        mainTextView.setText("Set in Java!");

        Button mainButton = (Button) findViewById(R.id.button1);
        mainButton.setOnClickListener(this);
    }

//    public String parserTest() {
//        JsonUtil jsonU = new JsonUtil();
//        Person person = new Person();
//        person.setName("Fernando");
//        person.setSurname("Cortes");
//
//        person.getAddress().setCity("9 de Julio");
//        person.getAddress().setAddress("Mitre 576");
//        person.getAddress().setState("Buenos Aires");
//
//        person.getNum1().setNumber("0800 123456");
//        person.getNum1().setType("casa");
//        person.getNum2().setNumber("15 1335545654");
//        person.getNum2().setType("cel");
//
////        jsonU.toJSon(person);
//
//        return jsonU.toJSon(person).toString();
//
////        System.out.println(jsonU.toJSon(person).toString());
////
////        Person person2 = jsonU.toPerson(jsonU.toJSon(person));
//    }

    @Override
    public void onClick(View v) {
//        TextView mainTextView = (TextView) findViewById(R.id.textView);
//        mainTextView.setText("Button pressed!");

        Intent logIn = new Intent(this, LogInActivity.class);
        startActivity(logIn);
        finish();
//        if (!post.isCancelled())
//            post.cancel(true);

    }

//    public void displayWelcome() {
//
//        // Access the device's key-value storage
//        mSharedPreferences = getSharedPreferences(PREFS, MODE_PRIVATE);
//
//
//        // Read the user's name,
//        // or an empty string if nothing found
//        String name = mSharedPreferences.getString(PREF_NAME, "");
//
//        if (name.length() > 0) {
//
//            // If the name is valid, display a Toast welcoming them
//            Toast.makeText(this, "Welcome back, " + name + "!", Toast.LENGTH_LONG).show();
//        } else {
//
//            // otherwise, show a dialog to ask for their name
//            AlertDialog.Builder alert = new AlertDialog.Builder(this);
//            alert.setTitle("Hello!");
//            alert.setMessage("What is your name?");
//
//            // Create EditText for entry
//            final EditText input = new EditText(this);
//            alert.setView(input);
//
//            // Make an "OK" button to save the name
//            alert.setPositiveButton("OK", new DialogInterface.OnClickListener() {
//
//                public void onClick(DialogInterface dialog, int whichButton) {
//
//                    // Grab the EditText's input
//                    String inputName = input.getText().toString();
//
//                    // Put it into memory (don't forget to commit!)
//                    SharedPreferences.Editor e = mSharedPreferences.edit();
//                    e.putString(PREF_NAME, inputName);
//                    e.commit();
//
//                    // Welcome the new user
//                    Toast.makeText(getApplicationContext(), "Welcome, " + inputName + "!", Toast.LENGTH_LONG).show();
//                }
//            });
//
//            // Make a "Cancel" button
//            // that simply dismisses the alert
//            alert.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
//
//                public void onClick(DialogInterface dialog, int whichButton) {
//
//                }
//            });
//
//            alert.show();
//        }
//    }
}
