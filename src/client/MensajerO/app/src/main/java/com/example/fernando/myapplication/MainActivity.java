package com.example.fernando.myapplication;

import android.content.Context;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Pair;
import android.view.Menu;
import android.view.MenuItem;

public class MainActivity extends ActionBarActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        new ServletPostAsyncTask().execute(new Pair<Context, String>(this, "Grupo Taller II"));

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
}
