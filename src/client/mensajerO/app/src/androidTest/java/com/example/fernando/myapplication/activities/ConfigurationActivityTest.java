package com.example.fernando.myapplication.activities;

import android.app.Instrumentation;
import android.test.ActivityInstrumentationTestCase2;
import android.widget.Button;
import android.widget.EditText;

import com.example.fernando.myapplication.Activities.ConfigurationActivity;
import com.example.fernando.myapplication.Activities.LogInActivity;
import com.example.fernando.myapplication.Activities.SignUpActivity;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Mocks.Server;
import com.example.fernando.myapplication.R;

/*
Prueba hacer cambios, apretar el boton Cancel y no se guardan los cambios, se
pasa a ChatsHallActivity.
Prueba hacer cambios, apretar Done y pasar a ChatsHallActivity y ver que los cambios
han sido guardados.
Prueba que pasa si el server no responde.
 */
public class ConfigurationActivityTest extends
        ActivityInstrumentationTestCase2<ConfigurationActivity> {

    private ConfigurationActivity activity;
    private EditText username;
    private EditText password;
    private Button backtologin;
    private Button signupbutton;
    Instrumentation.ActivityMonitor receiverActivityMonitor;

    public ConfigurationActivityTest() {
        super(ConfigurationActivity.class);
    }

    @Override
    protected void setUp() throws Exception {
        super.setUp();
        setActivityInitialTouchMode(false);
        activity = getActivity();
        Constants.server = new Server();
        Constants.server.setSharedPref(LogInActivity.getmSharedPref());

        username = (EditText) activity.findViewById(R.id.txtUsername);
        password = (EditText) activity.findViewById(R.id.txtPassword);
        backtologin = (Button) activity.findViewById(R.id.backtologin);
        signupbutton = (Button) activity.findViewById(R.id.signupbutton);

        //Create and add an ActivityMonitor to monitor interaction between the system and the
        //ReceiverActivity
        receiverActivityMonitor = getInstrumentation()
                .addMonitor(SignUpActivity.class.getName(), null, false);
    }

}
