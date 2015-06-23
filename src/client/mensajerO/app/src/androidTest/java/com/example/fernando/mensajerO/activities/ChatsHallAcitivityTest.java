package com.example.fernando.mensajerO.activities;

import android.app.Instrumentation;
import android.test.ActivityInstrumentationTestCase2;
import android.widget.Button;
import android.widget.EditText;

import com.fiuba.tallerii.mensajer0.Activities.ChatsHallActivity;
import com.fiuba.tallerii.mensajer0.Activities.LogInActivity;
import com.fiuba.tallerii.mensajer0.Activities.SignUpActivity;
import com.fiuba.tallerii.mensajer0.Common.Constants;
import com.fiuba.tallerii.mensajer0.Mocks.Server;
import com.example.fernando.mensajerO.R;

/*
Prueba que pase a ConfigurationActivity apretando el boton Settings del menu.
Prueba que pase a LogInActivity apretando el boton LogOut del menu.
Prueba que pase a UsersActivity apretando el boton Users en la ActionBar.
Prueba que muestre todos los chats que tiene un usuario.
Prueba que tocando uno de los chats se pase a ChatActivity con el usuario correcto.
Prueba el refrescado de los chats si otro usuario empieza un chat con el usuario
con el que tenemos la sesion abierta. Que pasa si se agrega un chat a la lista de
chats del usuario.
Prueba eliminar un chat de la lista de usuarios desde la vista, que se borre de la
lista de chats del usuario y que no lo vuelva a mandar el server.
Prueba que pasa si el server no responde.
 */
public class ChatsHallAcitivityTest extends
        ActivityInstrumentationTestCase2<ChatsHallActivity> {

    private ChatsHallActivity activity;
    private EditText username;
    private EditText password;
    private Button backtologin;
    private Button signupbutton;
    Instrumentation.ActivityMonitor receiverActivityMonitor;

    public ChatsHallAcitivityTest() {
        super(ChatsHallActivity.class);
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
