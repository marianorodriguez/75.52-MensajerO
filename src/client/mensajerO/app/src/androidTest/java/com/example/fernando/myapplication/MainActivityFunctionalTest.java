package com.example.fernando.myapplication;

import android.app.Instrumentation;
import android.test.ActivityInstrumentationTestCase2;
import android.test.TouchUtils;
import android.widget.Button;

import com.example.fernando.myapplication.Activities.GetInActivity;
import com.example.fernando.myapplication.Activities.LogInActivity;

public class MainActivityFunctionalTest extends
        ActivityInstrumentationTestCase2<GetInActivity> {

    private GetInActivity activity;

    public MainActivityFunctionalTest() {
        super(GetInActivity.class);
    }

    @Override
    protected void setUp() throws Exception {
        super.setUp();
        setActivityInitialTouchMode(false);
        activity = getActivity();
    }

    public void testStartSecondActivity() throws Exception {

        Button b = (Button) activity.findViewById(R.id.backtologin);
        String a = b.getText().toString();
//        buttonId = R.id.button1;
//        assertNotNull(activity.findViewById(buttonId));
//        Button view = (Button) activity.findViewById(buttonId);
        assertEquals("Incorrect label of the button", "Get In",a);

//        b.performClick();

        assertEquals("Text incorrect", "Started", "Started");

        // add monitor to check for the second activity
        Instrumentation.ActivityMonitor monitor =
                getInstrumentation().
                        addMonitor(LogInActivity.class.getName(), null, false);
//
//        // find button and click it
//        Button view = (Button) activity.findViewById(R.id.button1);
//
//        // TouchUtils handles the sync with the main thread internally
        TouchUtils.clickView(this, b);
//
//        // to click on a click, e.g., in a listview
//        // listView.getChildAt(0);
//
//        // wait 2 seconds for the start of the activity
        LogInActivity startedActivity = (LogInActivity) monitor
                .waitForActivityWithTimeout(2000);
        assertNotNull(startedActivity);
//
//        // search for the textView
//        TextView textView = (TextView) startedActivity.findViewById(R.id.resultText);
//
//        // check that the TextView is on the screen
//        ViewAsserts.assertOnScreen(startedActivity.getWindow().getDecorView(),
//                textView);
//        // validate the text on the TextView
//        assertEquals("Text incorrect", "Started", textView.getText().toString());
//
//        // press back and click again
//        this.sendKeys(KeyEvent.KEYCODE_BACK);
//
//        TouchUtils.clickView(this, view);
    }

}
