package com.example.fernando.mensajerO.activities;

import android.app.Instrumentation;
import android.content.SharedPreferences;
import android.test.ActivityInstrumentationTestCase2;
import android.test.TouchUtils;
import android.widget.Button;
import android.widget.EditText;

import com.fiuba.tallerii.mensajer0.Activities.ChatsHallActivity;
import com.fiuba.tallerii.mensajer0.Activities.LogInActivity;
import com.fiuba.tallerii.mensajer0.Activities.SignUpActivity;
import com.fiuba.tallerii.mensajer0.Common.Constants;
import com.fiuba.tallerii.mensajer0.Entities.User;
import com.fiuba.tallerii.mensajer0.Mocks.Server;
import com.example.fernando.mensajerO.R;

/*
Prueba el intento de loguearse con un usuario que no existe.
Prueba el intento de logueo con credenciales vacias.
Prueba el logueo con un usuario que si existe y el paso a ChatsHallActivity.
Prueba el logueo con un usuario que si existe pero con password incorrecta.
Prueba el paso a SignUpActivity con el boton Sign Up.
Prueba el server no responde.
 */
public class LogInActivityTest extends
        ActivityInstrumentationTestCase2<LogInActivity> {

    private LogInActivity activity;
    private EditText username;
    private EditText password;
    private Button loginbutton;
    private Button signupbutton;
    Instrumentation.ActivityMonitor receiverActivityMonitor;

    public LogInActivityTest() {
        super(LogInActivity.class);
    }

    @Override
    protected void setUp() throws Exception {
        super.setUp();
        setActivityInitialTouchMode(false);
        activity = getActivity();
        Constants.server = new Server();
        SharedPreferences sharedPref = LogInActivity.getmSharedPref();
        Constants.server.setSharedPref(sharedPref);

        username = (EditText) activity.findViewById(R.id.txtUsername);
        password = (EditText) activity.findViewById(R.id.txtPassword);
        loginbutton = (Button) activity.findViewById(R.id.backtologin);
        signupbutton = (Button) activity.findViewById(R.id.signupbutton);

        //Create and add an ActivityMonitor to monitor interaction between the system and the
        //ReceiverActivity
        receiverActivityMonitor = getInstrumentation()
                .addMonitor(LogInActivity.class.getName(), null, false);

    }

    @Override
    public void sendKeys(String keysSequence) {
        super.sendKeys(keysSequence);
    }

    //con credenciales "UsernameX" y "passwordX"
    public void testFailedLoginA() {

        //Escribo el username
        getInstrumentation().runOnMainSync(new Runnable() {
            @Override
            public void run() {
                username.requestFocus();
            }
        });
        getInstrumentation().waitForIdleSync();
        getInstrumentation().sendStringSync("usernameX");
        getInstrumentation().waitForIdleSync();

        //Escribo la password
        getInstrumentation().runOnMainSync(new Runnable() {
            @Override
            public void run() {
                password.requestFocus();
            }
        });
        getInstrumentation().waitForIdleSync();
        getInstrumentation().sendStringSync("passwordX");
        getInstrumentation().waitForIdleSync();

        Instrumentation.ActivityMonitor monitor =
                getInstrumentation().
                        addMonitor(ChatsHallActivity.class.getName(), null, false);

        TouchUtils.clickView(this, loginbutton);

        ChatsHallActivity startedActivity = (ChatsHallActivity) monitor
                .waitForActivityWithTimeout(2000);

        assertNull(startedActivity);
    }

    //con credenciales vacias "" y ""
    public void testFailedLoginB() {

        //Escribo el username
        getInstrumentation().runOnMainSync(new Runnable() {
            @Override
            public void run() {
                username.requestFocus();
            }
        });
        getInstrumentation().waitForIdleSync();
        getInstrumentation().sendStringSync("");
        getInstrumentation().waitForIdleSync();

        //Escribo la password
        getInstrumentation().runOnMainSync(new Runnable() {
            @Override
            public void run() {
                password.requestFocus();
            }
        });
        getInstrumentation().waitForIdleSync();
        getInstrumentation().sendStringSync("");
        getInstrumentation().waitForIdleSync();

        Instrumentation.ActivityMonitor monitor =
                getInstrumentation().
                        addMonitor(ChatsHallActivity.class.getName(), null, false);

        TouchUtils.clickView(this, loginbutton);

        ChatsHallActivity startedActivity = (ChatsHallActivity) monitor
                .waitForActivityWithTimeout(2000);

        assertNull(startedActivity);
    }

    //creo un user con "usernameX" y "passwordX" y luego accedo a el mediante el logIn
    public void testSuccesfullLogin() {

        String passwordMd5 = LogInActivity.md5("passwordX");
        User currentUser = new User("usernameX", passwordMd5);
        currentUser.location = "Unknowkn";
        currentUser.status = "online";
        currentUser.profile_picture = null;
        String package_ = Constants.packager.wrap("signUp", currentUser);
        Constants.server.signUp(package_);

        //Escribo el username
        getInstrumentation().runOnMainSync(new Runnable() {
            @Override
            public void run() {
                username.requestFocus();
            }
        });
        getInstrumentation().waitForIdleSync();
        getInstrumentation().sendStringSync("usernameX");
        getInstrumentation().waitForIdleSync();

        //Escribo la password
        getInstrumentation().runOnMainSync(new Runnable() {
            @Override
            public void run() {
                password.requestFocus();
            }
        });
        getInstrumentation().waitForIdleSync();
        getInstrumentation().sendStringSync("passwordX");
        getInstrumentation().waitForIdleSync();

        Instrumentation.ActivityMonitor monitor =
                getInstrumentation().
                        addMonitor(ChatsHallActivity.class.getName(), null, false);

        TouchUtils.clickView(this, loginbutton);

        ChatsHallActivity startedActivity = (ChatsHallActivity) monitor
                .waitForActivityWithTimeout(2000);

        assertNotNull(startedActivity);
    }

    // usernameX y passwordY
    public void testFailedLoginC () {
        assertEquals(true, false);
    }

    public void testGoToSignUp() {

        Instrumentation.ActivityMonitor monitor =
                getInstrumentation().
                        addMonitor(SignUpActivity.class.getName(), null, false);

        TouchUtils.clickView(this, signupbutton);

        SignUpActivity startedActivity = (SignUpActivity) monitor
                .waitForActivityWithTimeout(2000);

        assertNotNull(startedActivity);

        Button back = (Button) startedActivity.findViewById(R.id.backtologin);
        TouchUtils.clickView(this, back);

    }

//    public void testServerNotAnswering() {
//        Constants.server = null; //Pongo el server real que esta apagado.
//
//        String passwordMd5 = LogInActivity.md5("passwordX");
//        User currentUser = new User("usernameX", passwordMd5);
//        currentUser.location = "Unknowkn";
//        currentUser.status = "online";
//        currentUser.profile_picture = null;
//        String package_ = Constants.packager.wrap("signUp", currentUser);
//
//        LogInPostAsyncTask logInPost = new LogInPostAsyncTask();
//
//        logInPost.execute(new Pair<>(context, package_),
//                new Pair<>(context, Constants.logInUrl),
//                new Pair<>(context, "post"));
//
//        //Escribo el username
//        getInstrumentation().runOnMainSync(new Runnable() {
//            @Override
//            public void run() {
//                username.requestFocus();
//            }
//        });
//        getInstrumentation().waitForIdleSync();
//        getInstrumentation().sendStringSync("usernameX");
//        getInstrumentation().waitForIdleSync();
//
//        //Escribo la password
//        getInstrumentation().runOnMainSync(new Runnable() {
//            @Override
//            public void run() {
//                password.requestFocus();
//            }
//        });
//        getInstrumentation().waitForIdleSync();
//        getInstrumentation().sendStringSync("passwordX");
//        getInstrumentation().waitForIdleSync();
//
//        Instrumentation.ActivityMonitor monitor =
//                getInstrumentation().
//                        addMonitor(ChatsHallActivity.class.getName(), null, false);
//
//        TouchUtils.clickView(this, loginbutton);
//
//        ChatsHallActivity startedActivity = (ChatsHallActivity) monitor
//                .waitForActivityWithTimeout(2000);
//
//        assertNull(startedActivity);
//
//    }

}
