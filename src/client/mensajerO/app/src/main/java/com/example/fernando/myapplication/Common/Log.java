package com.example.fernando.myapplication.Common;

/**
 * Created by fernando on 01/06/15.
 */

//El servidor debe constar con un sistema de log en donde se registren los eventos que se
//generen durante la ejecución del mismo. El sistema de log debe permitir configurar el nível de
//los eventos que desean registrar. Estos níveles son:
//
//Error:  Condición de falla catastrófica, el sistema no puede funcionar. (criterio de las 2 a.m.)
//Condición que haga que la aplicación no pueda ejecutar una funcionalidad.
    //Ejemplo:
    //No es posible conectarse con la base de datos
//Warn:  Cualquier condición anómala que afecte el funcionamiento del sistema, pero no impida la
//funcionalidad básica
    //Ejemplos:
    //Uso de APIs deprecadas
    //Mal uso de APIs
//Info:  Cualquier acción correspondiente a un caso de uso iniciada por el usuario o el sistema.
//Información que permita trazar el historial de las entidades.
    //Ejemplos:
    //Conexión a la base de datos exitosa
    //Conexión de nuevo cliente
//Debug: Información de contexto que permita resolver un problema técnico. Debe ser útil incluso sin
//el código fuente
    //Ejemplo:
    //Datos de login para la DB

public class Log {
}
