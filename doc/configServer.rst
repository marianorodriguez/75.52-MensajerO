Configuración del servidor
==========================

Se puede configurar el servidor a través de linea de comando o un archivo *.json*.
El servidor se inicia con parámetros default, si encuentra el archivo de configuración (cuya ubicación default es **config/config.json**), utiliza los valores cargados en el archivo.

Si se especifica una configuración por parámetros de la linea de comando, los mismos sobreescriben a los cargados desde el archivo de configuración (y por consiguiente, a los default)

Configuración del logger
------------------------

La configuración del logger por defecto es la siguiente:

    { 
    "logger" : {
          "logDir" : "log.txt",
          "DEBUG" : true,
          "ERROR" : true,
          "INFO" : true,
          "WARNING" : true
       }
    }

* **logDir** : Dirección del archivo de log. Si no existe, se crea.
* **[DEBUG|ERROR|INFO|WARNING]** : Habilita o deshabilita el nivel correspondiente de log.
 
Configuración del server
------------------------

El nodo de la configuración del server no está presente en el archivo config.json, pero su formato es el siguiente

    { 
    "server" : {
          "port" : 8081,
          "database" : "path/to/database",
          "pollDelay" : 1000,
          "aliveTime" : 5
       }
    }

El nodo debe encontrarse a la misma altura que logger, y todos sus hijos son opcionales.

* **port** : Puerto al que se conecta el cliente.
* **database** : Dirección de las bases de datos. Dentro de él se crearán los directorios "users" y "chats" donde se persistirán todos los datos de los usuarios y mensajes enviados.
* **pollDelay**: Tiempo entre lecturas al socket de parte del servidor mongoose, en milisegundos.
* **aliveTime**: Tiempo que tarda un usuario en convertirse en desconectado, en segundos.

