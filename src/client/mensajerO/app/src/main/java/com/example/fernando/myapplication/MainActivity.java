package com.example.fernando.myapplication;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Pair;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends ActionBarActivity implements View.OnClickListener{

    private static final String PREFS = "prefs";
    private static final String PREF_NAME = "Fer";
    SharedPreferences mSharedPreferences;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
//
//        //BARRA DE PROGRESO
//        requestWindowFeature(Window.FEATURE_INDETERMINATE_PROGRESS);
//        setProgressBarIndeterminateVisibility(false);
//        //BARRA DE PROGRESO ON previo al request, OFF desp del request
//        setProgressBarIndeterminateVisibility(true);
        new ServletPostAsyncTask().execute(new Pair<Context, String>(this, "Grupo Taller II"));
//        setProgressBarIndeterminateVisibility(false);

        //JSON
        parserTest();

        TextView mainTextView = (TextView) findViewById(R.id.textView);
        mainTextView.setText("Set in Java!");

        Button mainButton = (Button) findViewById(R.id.main_button);
        mainButton.setOnClickListener(this);

        // 7. Greet the user, or ask for their name if new
        displayWelcome();

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    public void parserTest() {
        JsonUtil jsonU = new JsonUtil();
        Person person = new Person();
        person.setName("Fernando");
        person.setSurname("Cortes");

        person.getAddress().setCity("9 de Julio");
        person.getAddress().setAddress("Mitre 576");
        person.getAddress().setState("Buenos Aires");

        person.getNum1().setNumber("0800 123456");
        person.getNum1().setType("casa");
        person.getNum2().setNumber("15 1335545654");
        person.getNum2().setType("cel");

//        jsonU.toJSon(person);

        System.out.println(jsonU.toJSon(person).toString());

        Person person2 = jsonU.toPerson(jsonU.toJSon(person));
    }

    @Override
    public void onClick(View v) {
        TextView mainTextView = (TextView) findViewById(R.id.textView);
        mainTextView.setText("Button pressed!");

        // create an Intent to take you over to a new DetailActivity
        Intent detailIntent = new Intent(this, OtherActivity.class);

        // pack away the data about the cover
        // into your Intent before you head out
        detailIntent.putExtra("coverID", "undato");

        // TODO: add any other data you'd like as Extras

        // start the next Activity using your prepared Intent
        startActivity(detailIntent);

    }

    public void displayWelcome() {

        // Access the device's key-value storage
        mSharedPreferences = getSharedPreferences(PREFS, MODE_PRIVATE);


        // Read the user's name,
        // or an empty string if nothing found
        String name = mSharedPreferences.getString(PREF_NAME, "");

        if (name.length() > 0) {

            // If the name is valid, display a Toast welcoming them
            Toast.makeText(this, "Welcome back, " + name + "!", Toast.LENGTH_LONG).show();
        } else {

            // otherwise, show a dialog to ask for their name
            AlertDialog.Builder alert = new AlertDialog.Builder(this);
            alert.setTitle("Hello!");
            alert.setMessage("What is your name?");

            // Create EditText for entry
            final EditText input = new EditText(this);
            alert.setView(input);

            // Make an "OK" button to save the name
            alert.setPositiveButton("OK", new DialogInterface.OnClickListener() {

                public void onClick(DialogInterface dialog, int whichButton) {

                    // Grab the EditText's input
                    String inputName = input.getText().toString();

                    // Put it into memory (don't forget to commit!)
                    SharedPreferences.Editor e = mSharedPreferences.edit();
                    e.putString(PREF_NAME, inputName);
                    e.commit();

                    // Welcome the new user
                    Toast.makeText(getApplicationContext(), "Welcome, " + inputName + "!", Toast.LENGTH_LONG).show();
                }
            });

            // Make a "Cancel" button
            // that simply dismisses the alert
            alert.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {

                public void onClick(DialogInterface dialog, int whichButton) {}
            });

            alert.show();
        }
    }
}
