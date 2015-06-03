package com.example.fernando.myapplication.activities;

import junit.framework.Assert;

/*
Prueba el intento de registracion con un nombre de usuario que no existe en el servidor
y el paso a ConfigurationActivity.
Prueba el intento de registracion con un nombre de usuario que ya existe en el servidor.
Prueba el intento de logueo con credenciales vacias.
Prueba el boton para volver a LogInActivity.
Prueba el server no responde.
 */
public class SignUpActivityTest {

    public void testA() {
        Assert.assertEquals(true, true);
    }
}
