package com.example.fernando.myapplication.activities;

import android.app.Instrumentation;
import android.test.ActivityInstrumentationTestCase2;
import android.widget.Button;
import android.widget.EditText;

import com.example.fernando.myapplication.Activities.ChatActivity;
import com.example.fernando.myapplication.Activities.LogInActivity;
import com.example.fernando.myapplication.Activities.SignUpActivity;
import com.example.fernando.myapplication.Activities.UsersActivity;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Mocks.Server;
import com.example.fernando.myapplication.R;

/*
Prueba que se muestren los mensajes anteriores con ese usuario.
Prueba aniadir un nuevo mensaje del otro usuario al chat y ver qe se refresque el chat
y aparezca.
Prueba escribir un nuevo mensaje y apretar el boton SEND y que se agregue al chat.
Prueba que pasa si no responde el servidor.
 */
public class ChatActivityTest extends
        ActivityInstrumentationTestCase2<ChatActivity> {

    private ChatActivity activity;
    private EditText username;
    private EditText password;
    private Button backtologin;
    private Button signupbutton;
    Instrumentation.ActivityMonitor receiverActivityMonitor;

    public ChatActivityTest() {
        super(ChatActivity.class);
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
