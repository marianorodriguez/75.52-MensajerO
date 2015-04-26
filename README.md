75.52-MensajerO
===============

Taller de Programacion II
-------------------------

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

Para compilar las pruebas:

    $ make tests

Para compilar el servidor:

    $ make server

Para limpiar el proyecto:

    $ make clean

Para correr coverage de las pruebas

* Si el proyecto fue compilado con soporte para coverage, correr desde *src/server*

    $ tests/tests
    $ lcov -c -d main/ -o testOutput.info
    $ genhtml testOutput.info --output-directory=report

* Para reiniciar los contadores (en caso de que se quiera volver a correr las pruebas)

    $ lcov -z -d main/
