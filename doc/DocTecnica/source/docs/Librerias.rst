.. index:: Librerías

Librerías
************
Para el funcionamiento de la aplicación se decidieron utilizar algunas librerías para ayudar en la implementación de algunos servicios. A excepción de rocksdb, el resto de las librerías ya se encuentran compiladas una vez que se baja el proyecto. 

Base de datos.
------------
Para la base de datos del servidor se utilizó la librería **rocksdb** (http://rocksdb.org/), versión 3.10.0. Esta librería permite la persistencia de una estructura de datos que asocia *claves* con *valores*. Debido al peso de esta librería, esta es la única que es necesario compilar en el primer uso del servidor. 

Servidor HTTP
------------
Para el servidor HTTP de la aplicación se utilizó **mongoose** (https://github.com/cesanta/mongoose). Este servidor web facilitó la creación de una conexión entre la aplicación del celular y el servidor. 

Json
-------------
Para el intercambio de datos se conto con **jsonpp** (https://github.com/open-source-parsers/jsoncpp). Esta biblioteca se uso en la persistencia de los datos y en los intercambios entre servidor y cliente. 

Compilación
************
Para la compilación del servidor se utilizó **CMake** , el cual genera un Makefile. Mediante este Makefile, se puede luego compilar el servidor o las pruebas.

Como compilar
------------
Desde consola dirigirse a la carpeta del proyecto y ejecutar los siguientes comandos:

Instalar dependencias

    $ sudo apt-get install g++ cmake libbz2-dev zlib1g-dev libcppunit-dev libcurl4-gnutls-dev 

	Además, si se quieren ejecutar las pruebas de coverage, se deberá ingresar:

    $ sudo apt-get install lcov


Compilar rocksdb

    $ cd src/server/3rd-party/rocksdb

    $ make static_lib

Configurar script de compilación

    Desde *src/server* correr

    $ cmake .

    Si se quiere correr pruebas de coverage, se debe correr

    $ cmake . -Dcoverage-test=true

Se compila desde src/server:

Para compilar las pruebas:

    $ make tests

Para compilar el servidor:

    $ make server

Para limpiar el proyecto:

    $ make clean

Para facilitar la compilación, se encuentra el script prearmado **build.sh** en *src/server* el cual realiza todos estos pasos automaticamente. 
	
    $ ./build.sh

