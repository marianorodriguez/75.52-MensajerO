package com.example.fernando.myapplication.activities;

import android.app.Instrumentation;
import android.test.ActivityInstrumentationTestCase2;
import android.widget.Button;
import android.widget.EditText;

import com.example.fernando.myapplication.Activities.ChatsHallActivity;
import com.example.fernando.myapplication.Activities.LogInActivity;
import com.example.fernando.myapplication.Activities.SignUpActivity;
import com.example.fernando.myapplication.Activities.UsersActivity;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Mocks.Server;
import com.example.fernando.myapplication.R;

/*
Prueba que pase a UsersActivity apretando el boton Chats en la ActionBar.
Prueba que se muestren todos los usuarios que tiene el server.
Prueba que se agreguen usuarios a la vista cuando se agregan usuarios al server.
Prueba que no se muestren los usuarios con status offline en la lista de usuarios.
Prueba que pasa si el server no responde.
 */
public class UsersActivityTest extends
        ActivityInstrumentationTestCase2<UsersActivity> {

    private UsersActivity activity;
    private EditText username;
    private EditText password;
    private Button backtologin;
    private Button signupbutton;
    Instrumentation.ActivityMonitor receiverActivityMonitor;

    public UsersActivityTest() {
        super(UsersActivity.class);
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
