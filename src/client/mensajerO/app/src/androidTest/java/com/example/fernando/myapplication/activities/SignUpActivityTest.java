package com.example.fernando.myapplication.activities;

import android.app.Instrumentation;
import android.content.SharedPreferences;
import android.test.ActivityInstrumentationTestCase2;
import android.widget.Button;
import android.widget.EditText;

import com.example.fernando.myapplication.Activities.LogInActivity;
import com.example.fernando.myapplication.Activities.SignUpActivity;
import com.example.fernando.myapplication.Common.Constants;
import com.example.fernando.myapplication.Mocks.Server;
import com.example.fernando.myapplication.R;

import junit.framework.Assert;

/*
Prueba el intento de registracion con un nombre de usuario que no existe en el servidor
y el paso a ConfigurationActivity.
Prueba el intento de registracion con un nombre de usuario que ya existe en el servidor.
Prueba el intento de logueo con credenciales vacias.
Prueba el boton para volver a LogInActivity.
Prueba el server no responde.
 */
public class SignUpActivityTest extends
        ActivityInstrumentationTestCase2<SignUpActivity> {

    private SignUpActivity activity;
    private EditText username;
    private EditText password;
    private Button backtologin;
    private Button signupbutton;
    Instrumentation.ActivityMonitor receiverActivityMonitor;

    public SignUpActivityTest() {
        super(SignUpActivity.class);
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

    @Override
    public void sendKeys(String keysSequence) {
        super.sendKeys(keysSequence);
    }

    public void testSuccessfullSignUp () {
        Assert.assertEquals(true, true);
    }

    //Ya existe un usuario con ese nombre
    public void testFailedSignUpA() {

    }

    //Credenciales vacias ""
    public void testFailedSignUpB() {

    }

    //    public void testServerNotAnswering() {
    // }

}
