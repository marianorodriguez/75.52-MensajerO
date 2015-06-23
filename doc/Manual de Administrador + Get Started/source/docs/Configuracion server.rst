.. index:: Configuración.

Configuración.
**************

Hay varios parámetros que se pueden modificar en el servidor de MensajerO! para lograr el comportamiento deseado.
Se puede configurar el servidor a través de linea de comando o un archivo *.json*.
El servidor se inicia con parámetros default, si encuentra el archivo de configuración (cuya ubicación default es **config/config.json**), utiliza los valores cargados en el archivo.

.. figure::  images/serverInterface.png
   :align:   center


Mediante el archivo de configuración.
-------------------------------------

El archivo de configuración es una de las opciones que tenés para modificar los parámetros del servidor.
Por defecto, el archivo se llama "config.json" y se encuentra en la carpeta config.

::

	{   
		"logger" : {
			"logDir" : "log.txt",
			"DEBUG" : true,
			"ERROR" : true,
			"INFO" : true,
			"WARNING" : true
		},

		"server" : {
			"port" : 8081,
			"database" : "database",
			"pollDelay" : 1000,
			"aliveTime" : 5000
		}
	}


Si se especifica una configuración por parámetros de la linea de comando, los mismos sobreescriben a los cargados desde el archivo de configuración (y por consiguiente, a los default)

Configuración del logger.
.........................

La configuración del logger por defecto es la siguiente::

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
	* true: habilitado.
	* false: deshabilitado.
 
Configuración del servidor.
...........................

La configuración del servidor por defecto es la siguiente::

    { 
    "server" : {
          "port" : 8081,
          "database" : "path/to/database",
          "pollDelay" : 1000,
          "aliveTime" : 5000
       }
    }

El nodo es opcional, debe encontrarse a la misma altura que logger, y todos sus hijos son opcionales.

* **port** : Puerto al que se conecta el cliente.
* **database** : Dirección de las bases de datos. Dentro de él se crearán los directorios "users" y "chats" donde se persistirán todos los datos de los usuarios y mensajes enviados.
* **pollDelay**: Tiempo entre lecturas al socket de parte del servidor mongoose, en milisegundos.
* **aliveTime**: Tiempo que tarda un usuario en convertirse en desconectado, en segundos.


Mediante la linea de comandos.
------------------------------

Archivo de configuración.
.........................
::

	-c <path>
	--config <path>

Mediante la línea de comandos podés configurar la ruta al archivo de configuración. Esto hace que los parametros que no ingreses por linea de comandos sean leidos del archivo.

Su valor por defecto es **"config/config.json"**

Ejemplo de uso::

	./run.sh -c "config/nuevaConfig.json"
	./run.sh --config "archivoConfiguracion.json"


Numero de puerto.
.................
::

	-p <port>
	--port <port>

Número de puerto del servidor.
Similar al "port" del archivo de configuración, su valor por defecto es 8081.

Ejemplo de uso::

	./run.sh -p 8081
	./run.sh --port 8081


Dirección IP.
.............

Aunque este no es un parametro que se pueda configurar manualmente, se muestra para facilitarle al usuario de MensajerO! la configuración de este número dentro de la aplicación.


Ruta de la Base de Datos.
.........................

::

	-d <path>
	--database <path>

Donde el servidor de MensajerO! guarda toda la información de sus usuarios, así como los mensajes y los chats.

Ejemplo de uso::

	./run.sh -d "servidorBD/base"
	./run.sh --database "database/nuevaBD"

Similar al "database" del archivo de configuración, su valor por defecto es "/database".

.. warning:: Tené en cuenta que modificar la ruta de la base de datos del servidor puede implicar que los usuarios de la aplicación no puedan recolectar la información que necesiten. 
.. warning:: En MensajerO! Inc. no nos hacemos responsables de las pérdidas de datos que implique modificar este parámetro.

Tiempo de vida del cliente.
...........................

::

	-a <msec>
	--aliveTime <msec>

En milisegundos, se refiere al tiempo máximo de inactividad que tiene un usuario de MensajerO! hasta que se lo considera desconectado.
El tiempo de inactividad comienza cuando el usuario cierra o minimiza la aplicación.

Ejemplo de uso::

	./run.sh -a 4000
	./run.sh --aliveTime 6000

Similar al "aliveTime" del archivo de configuración, su valor por defecto es 5000.

.. warning:: Tené en cuenta que si este valor es menor a 2000, el cliente podría experimentar la pérdida de conexión con el servidor.

Tiempo de escucha del servidor.
...............................

::

	-P <msec>
	--pollDelay <msec>

En milisegundos, se refiere al tiempo que el servidor dejará pasar hasta atender la próxima consulta de un usuario.

Ejemplo de uso::

	./run.sh -P 1000
	./run.sh --pollDelay 300

Similar al "pollDelay" del archivo de configuración, su valor por defecto es 1000.

.. tip:: Es recomendable que este valor sea menor al tiempo de vida del cliente.

.. warning:: Tené en cuenta que si este tiempo es superior al tiempo de vida del cliente, podría empezar a fallar la detección de usuarios conectados.

.. warning:: Tené en cuenta que si este valor es muy alto, el servidor tardará mucho tiempo en atender cada consulta, lo que puede provocar una severa disminución en la velocidad del servicio.
