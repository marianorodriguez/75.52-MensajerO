package com.example.fernando.myapplication.activities;

import android.app.Instrumentation;
import android.test.ActivityInstrumentationTestCase2;
import android.test.TouchUtils;
import android.widget.Button;
import android.widget.EditText;

import com.example.fernando.myapplication.Activities.GetInActivity;
import com.example.fernando.myapplication.Activities.LogInActivity;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.R;

import junit.framework.Assert;

/**
 * Created by fernando on 19/04/15.
 */

/*
Prueba que el ip ingresado en GetInActivity quede configurado en la siguiente
activity y que el botton de Get In lleva a la LogInActivity
*/
public class GetInActivityTest extends
        ActivityInstrumentationTestCase2<GetInActivity> {

    private GetInActivity activity;

    public GetInActivityTest() {
        super(GetInActivity.class);
    }

    @Override
    protected void setUp() throws Exception {
        super.setUp();
        setActivityInitialTouchMode(false);
        activity = getActivity();
    }

    @Override
    public void sendKeys(String keysSequence) {
        super.sendKeys(keysSequence);
    }

    public void test() {

        EditText ip = (EditText) activity.findViewById(R.id.ipedittext);

        final EditText senderMessageEditText = (EditText) activity
                .findViewById(R.id.ipedittext);

        //Create and add an ActivityMonitor to monitor interaction between the system and the
        //ReceiverActivity
        Instrumentation.ActivityMonitor receiverActivityMonitor = getInstrumentation()
                .addMonitor(GetInActivity.class.getName(), null, false);

        //Request focus on the EditText field. This must be done on the UiThread because
        getInstrumentation().runOnMainSync(new Runnable() {
            @Override
            public void run() {
                senderMessageEditText.requestFocus();
            }
        });
        //Wait until all events from the MainHandler's queue are processed
        getInstrumentation().waitForIdleSync();

        //Send the text message
        getInstrumentation().sendStringSync("192.168.1.100");
        getInstrumentation().waitForIdleSync();


//        ip.setText("192.168.1.100");
        String actualIp = ip.getText().toString();

        Button getinbutton = (Button) activity.findViewById(R.id.getinbutton);

        Instrumentation.ActivityMonitor monitor =
                getInstrumentation().
                        addMonitor(LogInActivity.class.getName(), null, false);

        TouchUtils.clickView(this, getinbutton);

        LogInActivity startedActivity = (LogInActivity) monitor
                .waitForActivityWithTimeout(2000);

        assertNotNull(startedActivity);

        Assert.assertEquals(actualIp, Constants.ipServer);
    }

}

