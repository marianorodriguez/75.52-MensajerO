README
---------

75.52-MensajerO


Taller de Programacion II


### Documentación

Además de este Readme, se encuentra documentación en formato restructured text, en el directorio *doc*.

Dentro de ese directorio se encuentra el informe correspondiente a la primer entrega de la aplicación, en la carpeta *informe*.
La documentación fue generada con sphinx-doc.

Para compilar se debe escribir make <formato de salida>.
En caso de no elegir ningún formato, se desplegará un texto informativo que indica que formatos se pueden elegir.

### Compilación

Desde consola dirigirse a la carpeta del proyecto y ejecutar los siguientes comandos:

Instalar dependencias

    $ sudo apt-get install libbz2-dev zlib1g-dev libcppunit-dev libcurl4-gnutls-dev

    Para generar reportes de las pruebas de coverage, además instalar el paquete "lcov"

Compilar rocksdb

    $ cd src/server/3rd-party/rocksdb
    $ make static_lib

Configurar script de compilación

    Desde *src/server* correr

    $ mkdir build
    $ cd build
    $ cmake ..

    Si se quiere correr pruebas de coverage, se debe correr

    $ cmake .. -Dcoverage-test=true

Se compila desde src/server:

Para compilar las pruebas:

    $ make tests

Para compilar el servidor:

    $ make server

Para limpiar el proyecto:

    $ make clean

### Scripts prearmados

Para facilitar la instalación de la aplicación, se armaron algunos scripts en bash que agrupan varios de los comandos detallados abajo.

**build.sh** : Compila la aplicación en una carpeta llamada *build*, y copia en su interior a *run.sh*, *runTests.sh*, *coverage.sh*. Además, si se le agrega el parametro "coverage" compila con soporte para pruebas de cobertura.

**run.sh** : Ejecuta el servidor, y crea una carpeta para las bases de datos si es necesario.

**runTests.sh** : Ejecuta las pruebas, limpiando los contenidos creados por pruebas anteriores, 

**coverage.sh** : Ejecuta las pruebas y recolecta los datos de los tests de coverage.


### Ejecutar servidor

Para correr el servidor, desde *src/server* ejecutar:

    $ mkdir -p database/users
    $ mkdir -p database/chats
    $ main/server

La aplicación soporta varios flags para la configuración:

* **-c**, **--config** <path/to/config.json>: dirección del archivo de configuración.
* **-p**, **--port** <numPuerto>: selecciona el puerto de escucha del servidor.
* **-d**, **--database** <path/to/db>: directorio de base de datos
* **-P**, **--pollDelay** <msec>: demora entre lecturas del socket(mongoose)
* **-a**, **--aliveTime** <msec>: tiempo que se considera que un usuario esta conectado

Para correr coverage de las pruebas

* Si el proyecto fue compilado con soporte para coverage, correr desde *src/server*

    $ tests/tests
    $ lcov -c -d main/ -o testOutput.info
    $ genhtml testOutput.info --output-directory=report

* Para reiniciar los contadores (en caso de que se quiera volver a correr las pruebas)

    $ lcov -z -d main/




FUNCIONALIDADES
---------

Servidor:

* Servicio de autenticación:
* Servicio para delivery de conversaciones:
* Servicio de delivery de difusión:
* Almacenamiento de conversaciones:
* Checkin de usuarios:
* Servicio de administración de perfil de usuario:
* Log:

Cliente:
* Autentificación:
* Registración:
* Checkin:
* Interfaz gráfica:
	Visualización de conversaciones:
	Lista de usuarios conectados:
	Envío de conversaciones:
	Visualización de estado de usuario:
	Configuración de perfil:

* Log:
* Instalación de aplicación:

CHANGELOG
---------

* 2015-05-02: Versión beta
Features:
	* El servidor recibe y atiende peticiones del tipo GET y POST.
	* El servidor puede registrar usuarios y almacenarlos en una base de datos.
	* El servidor puede leer todos los usuarios registrados previamente.
	* El servidor puede responder a una petición de login validando la contraseña almacenada del usuario.
	* El servidor puede cambiar los datos de un usuario registrado.

Known bugs / TODO:
	* Falta tests de varios servicios.
	* La configuración del servidor es ignorada.
	* Llamar a un servicio inexistente no devuelve ninguna respuesta, dejando al cliente en espera
	* Bajo uso del logger.
	* Enviar un mensaje resulta en una excepción no capturada debido a que no se asignan el emisor, receptor y mensaje correctamente.


Issues:
------

Closed Issues:

server - usersService
#51 opened by marianorodriguez

server - imAliveService
#50 opened by marianorodriguez 

server - gestion de conexiones
#49 opened by marianorodriguez 

Pruebas de usuario bug 
#48 opened by mlafroce 

server, client - cambiar nombres servicios 
#43 opened by marianorodriguez 

cliente - poner config y log out en settings 
#41 opened by fernandocortes10 

server - más pruebas para DB 
#40 opened by marianorodriguez 

server - contraseñas de usuarios 
#39 opened by marianorodriguez 

server - problema con prueba de Logger
#37 opened by marianorodriguez 

client, server - definir cuales van a ser los datos a transmitir entre ambos y en que formato. 
#36 opened by fernandocortes10 

client - hacer y aceitar flujo de activities (vacias) para todos los casos de la app. 
#35 opened by fernandocortes10 

Agregar keyword 'const' y referencias faltantes. 
#34 opened by mlafroce 
 
server - estructura DataBase 
#33 opened by marianorodriguez 
 
client - serializar y deserializar json's de clases java 
#32 opened by fernandocortes10 
 
client - conectar y hacer request a URL 
#31 opened by fernandocortes10 
 
server - Cliente rest para pruebas 
#30 opened by mlafroce 

server - Servidor mongoose 
#29 opened by mlafroce 
 
server - documentar Serializables y Exceptions 
#28 opened by marianorodriguez 
 
server - pruebas de DataBase 
#27 opened by marianorodriguez 
 
server - documentar interfaz y clases de IPersistable 
#26 opened by marianorodriguez 
 
server - arreglar CMake 
#25 opened by marianorodriguez 
 
Logger no se instancia correctamente. 
#24 opened by mlafroce 
 
server - implementar clase Chat, completar sus pruebas y documentar 
#23 opened by marianorodriguez 
 
server - implementar el time&date automático en Message 
#22 opened by marianorodriguez 
 
server - agregar mas pruebas a Message! 
#21 opened by marianorodriguez 

server - add documentation to Message and ISerializable enhancement 
#20 opened by marianorodriguez 
 
server - hash User passwords enhancement 
#19 opened by marianorodriguez 
 
server - remove "deserialize" method in ISerializables enhancement 
#18 opened by marianorodriguez 
 
server - fix Message constructor bug 
#17 opened by marianorodriguez 
 
server - add more tests to the logger enhancement 
#16 opened by marianorodriguez 

Open Issues:

refactor services enhancement 
#53 opened by marianorodriguez 

server - userConfigService simple task 
#52 opened by marianorodriguez 
 
server - Configuración general enhancement 
#47 opened by mlafroce 
 
cliente - configurar que cada activity llame al servicio que corresponda simple task 
#46 opened by fernandocortes10 
 
server - pruebas de integracion bug 
#45 opened by marianorodriguez 
 
server - diagrama de clases 
#44 opened by marianorodriguez 
 
cliente - crear servidor para hacer tests simple task 
#42 opened by fernandocortes10 
 
client - implementar utilities simple task 
#38 opened by marianorodriguez 


DIAGRAMA DE CLASES:
------------------

.. image:: diagramaDeClases.png

DIVISIÓN DE TAREAS:
------------------

Luego de diseñar el diagrama de clases, se dividió al servidor en 3 partes principales. De los 4 integrantes, 3 se dedicaron a desarrollar cada una de estas partes del servidor:

* Serializables : Mariano Rodríguez
* Base de Datos : Francisco Nery
* Conexión : Matías Lafroce

Luego de terminar los Serializables y la Base de Datos, los 2 integrantes se enfocaron en desarrollar la parte de la conexión y se dedicaron a empezar los servicios requeridos con sus pruebas. 

TODO: Referirse al tracking de issues en esta división de tareas. 

El úlitmo integrante, Fernando Cortés, se enfocó en el desarrollo de la aplicación del cliente en Android.

