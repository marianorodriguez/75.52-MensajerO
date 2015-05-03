package com.example.fernando.myapplication.Activities;

import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.NotificationCompat;
import android.support.v7.app.ActionBarActivity;
import android.view.View;
import android.widget.Button;

import com.example.fernando.myapplication.R;

public class GetInActivity extends ActionBarActivity implements View.OnClickListener{

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


//        User user = new User("Fernando", "Cortes");
//
//        String package1 = user.toJsonForServer().toString();
//
//        System.out.println(package1);
//
//        String packageWrapped = Constants.packager.wrap("logIn", user);
//
//        System.out.println(packageWrapped);
//
//        JSONObject packageUnwrapped = Constants.packager.unwrap(packageWrapped);
//
//        String pac = packageUnwrapped.toString();
//
//        try {
//            String username = packageUnwrapped.getString("username");
//
//            System.out.println(packageUnwrapped.toString());
//        } catch (JSONException e) {
//            e.printStackTrace();
//        }
//        System.out.println(packageUnwrapped.toString());


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

//public class GetInActivity extends Activity {
//
//    @Override
//    protected void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//        setContentView(R.layout.getin);
//
//        final ListView listview = (ListView) findViewById(R.id.listview);
//        String[] values = new String[] { "Android", "iPhone", "WindowsMobile",
//                "Blackberry", "WebOS", "Ubuntu", "Windows7", "Max OS X",
//                "Linux", "OS/2", "Ubuntu", "Windows7", "Max OS X", "Linux",
//                "OS/2", "Ubuntu", "Windows7", "Max OS X", "Linux", "OS/2",
//                "Android", "iPhone", "WindowsMobile" };
//
//        final ArrayList<String> list = new ArrayList<String>();
//        for (int i = 0; i < values.length; ++i) {
//            list.add(values[i]);
//        }
//        final StableArrayAdapter adapter = new StableArrayAdapter(this,
//                android.R.layout.simple_list_item_1, list);
//        listview.setAdapter(adapter);
//
//        listview.setOnItemClickListener(new AdapterView.OnItemClickListener() {
//
//            @TargetApi(Build.VERSION_CODES.JELLY_BEAN)
//            @Override
//            public void onItemClick(AdapterView<?> parent, final View view,
//                                    int position, long id) {
//                final String item = (String) parent.getItemAtPosition(position);
//                view.animate().setDuration(2000).alpha(0).withEndAction(new Runnable() {
//                    @Override
//                    public void run() {
//                        list.remove(item);
//                        adapter.notifyDataSetChanged();
//                        view.setAlpha(1);
//                    }
//                });
//            }
//
//        });
//    }
//
//    private class StableArrayAdapter extends ArrayAdapter<String> {
//
//        HashMap<String, Integer> mIdMap = new HashMap<>();
//
//        public StableArrayAdapter(Context context, int textViewResourceId,
//                                  ArrayList<String> objects) {
//            super(context, textViewResourceId, objects);
//            for (int i = 0; i < objects.size(); ++i) {
//                mIdMap.put(objects.get(i), i);
//            }
//        }
//
//        @Override
//        public long getItemId(int position) {
//            String item = getItem(position);
//            return mIdMap.get(item);
//        }
//
//        @Override
//        public boolean hasStableIds() {
//            return true;
//        }
//
//    }
//
//}

//public class GetInActivity extends ListActivity
//        implements LoaderManager.LoaderCallbacks<Cursor> {
//
//    // This is the Adapter being used to display the list's data
//    SimpleCursorAdapter mAdapter;
//
//    // These are the Contacts rows that we will retrieve
//    static final String[] PROJECTION = new String[] {ContactsContract.Data._ID,
//            ContactsContract.Data.DISPLAY_NAME};
//
//    // This is the select criteria
//    static final String SELECTION = "((" +
//            ContactsContract.Data.DISPLAY_NAME + " NOTNULL) AND (" +
//            ContactsContract.Data.DISPLAY_NAME + " != '' ))";
//
//    @Override
//    protected void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//
//        // Create a progress bar to display while the list loads
//        ProgressBar progressBar = new ProgressBar(this);
//        progressBar.setLayoutParams(new RadioGroup.LayoutParams(RadioGroup.LayoutParams.WRAP_CONTENT,
//                RadioGroup.LayoutParams.WRAP_CONTENT, Gravity.CENTER));
//        progressBar.setIndeterminate(true);
//        getListView().setEmptyView(progressBar);
//
//        // Must add the progress bar to the root of the layout
//        ViewGroup root = (ViewGroup) findViewById(android.R.id.content);
//        root.addView(progressBar);
//
//        // For the cursor adapter, specify which columns go into which views
//        String[] fromColumns = {ContactsContract.Data.DISPLAY_NAME};
//        int[] toViews = {android.R.id.text1}; // The TextView in simple_list_item_1
//
//        // Create an empty adapter we will use to display the loaded data.
//        // We pass null for the cursor, then update it in onLoadFinished()
//        mAdapter = new SimpleCursorAdapter(this,
//                android.R.layout.simple_list_item_1, null,
//                fromColumns, toViews, 0);
//        setListAdapter(mAdapter);
//
//        // Prepare the loader.  Either re-connect with an existing one,
//        // or start a new one.
//        getLoaderManager().initLoader(0, null, this);
//    }
//
//    // Called when a new Loader needs to be created
//    public Loader<Cursor> onCreateLoader(int id, Bundle args) {
//        // Now create and return a CursorLoader that will take care of
//        // creating a Cursor for the data being displayed.
//        return new CursorLoader(this, ContactsContract.Data.CONTENT_URI,
//                PROJECTION, SELECTION, null, null);
//    }
//
//    // Called when a previously created loader has finished loading
//    public void onLoadFinished(Loader<Cursor> loader, Cursor data) {
//        // Swap the new cursor in.  (The framework will take care of closing the
//        // old cursor once we return.)
//        mAdapter.swapCursor(data);
//    }
//
//    // Called when a previously created loader is reset, making the data unavailable
//    public void onLoaderReset(Loader<Cursor> loader) {
//        // This is called when the last Cursor provided to onLoadFinished()
//        // above is about to be closed.  We need to make sure we are no
//        // longer using it.
//        mAdapter.swapCursor(null);
//    }
//
//    @Override
//    public void onListItemClick(ListView l, View v, int position, long id) {
//        // Do something when a list item is clicked
//    }
//}


//public class GetInActivity extends ListActivity {
//    public void onCreate(Bundle icicle) {
//        super.onCreate(icicle);
//        String[] values = new String[] { "Android", "iPhone", "WindowsMobile",
//                "Blackberry", "WebOS", "Ubuntu", "Windows7", "Max OS X",
//                "Linux", "OS/2", "OS/2", "OS/2", "OS/2", "OS/2", "OS/2", "OS/2", "OS/2", "OS/2", "OS/2", "OS/2", "OS/2", "OS/2", "OS/2"
//                , "OS/2", "OS/2", "OS/2", "OS/2", "OS/2", "OS/2"};
//        // use your custom layout
//        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
//                R.layout.line, R.id.label, values);
//        setListAdapter(adapter);
//    }
//
//    @Override
//    protected void onListItemClick(ListView l, View v, int position, long id) {
//        String item = (String) getListAdapter().getItem(position);
//        Toast.makeText(this, item + " selected", Toast.LENGTH_LONG).show();
//    }
//}


//public class GetInActivity extends ActionBarActivity {

//    @Override
//    protected void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//        setContentView(R.layout.getin);
//
//        final ListView listview = (ListView) findViewById(R.id.listview);
//        String[] values = new String[] { "Android", "iPhone", "WindowsMobile",
//                "Blackberry", "WebOS", "Ubuntu", "Windows7", "Max OS X",
//                "Linux", "OS/2", "Ubuntu", "Windows7", "Max OS X", "Linux",
//                "OS/2", "Ubuntu", "Windows7", "Max OS X", "Linux", "OS/2",
//                "Android", "iPhone", "WindowsMobile" };
//
//        final ArrayList<String> list = new ArrayList<>();
//        for (int i = 0; i < values.length; ++i) {
//            list.add(values[i]);
//        }
//        final StableArrayAdapter adapter = new StableArrayAdapter(this,
//                android.R.layout.simple_list_item_1, list);
//        listview.setAdapter(adapter);
//
//        listview.setOnItemClickListener(new AdapterView.OnItemClickListener() {
//
//            @Override
//            public void onItemClick(AdapterView<?> parent, final View view,
//                                    int position, long id) {
//                final String item = (String) parent.getItemAtPosition(position);
//
////                adapter = null;
////                list.add("Andrea");
//
//                adapter.add("Andrea");
//                listview.setAdapter(adapter);
////                adapter.notifyDataSetChanged();
//
////                tirarToast();
////                view.animate().setDuration(2000).alpha(0)
////                        .withEndAction(new Runnable() {
////                            @Override
////                            public void run() {
////                                list.remove(item);
////
////
////                                list.add("Andrea");
////                                StableArrayAdapter adapter2 = new StableArrayAdapter(getApplicationContext(), android.R.layout.simple_list_item_1, list);
////                                listview.setAdapter(adapter2);
//////                                adapter2.notifyDataSetChanged();
////
//////                                adapter.notifyDataSetChanged();
////                                view.setAlpha(1);
////                            }
////                        });
//            }
//
//        });
//    }
//
//    private void tirarToast() {
//        Toast.makeText(this, "lala", Toast.LENGTH_LONG).show();
//    }
//
//    private class StableArrayAdapter extends ArrayAdapter<String> {
//
//        HashMap<String, Integer> mIdMap = new HashMap<>();
//
//        public StableArrayAdapter(Context context, int textViewResourceId,
//                                  ArrayList<String> objects) {
//            super(context, textViewResourceId, objects);
//            for (int i = 0; i < objects.size(); ++i) {
//                mIdMap.put(objects.get(i), i);
//            }
//        }
//
//        @Override
//        public long getItemId(int position) {
//            String item = getItem(position);
//            return mIdMap.get(item);
//        }
//
//        @Override
//        public boolean hasStableIds() {
//            return true;
//        }
//
//        @Override
//        public void add(String object) {
//            super.add(object);
//            mIdMap.size();
////            Toast.makeText(getApplicationContext(),mIdMap.size(), Toast.LENGTH_LONG ).show();
//            mIdMap.put(object, 23);
//        }
//
//
//
//    }

//    @Override
//    protected void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//        setContentView(R.layout.getin);
//
//        TextView mainTextView = (TextView) findViewById(R.id.textView2);
//        int i = 0;
//        while (i < 100) {
//            mainTextView.append("\n fer");
//            i++;
//        }
//    }
//
//}