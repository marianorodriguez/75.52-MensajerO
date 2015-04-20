75.52-MensajerO
===============

Taller de Programacion II
-------------------------

Desde consola dirigirse a la carpeta del proyecto y ejecutar los siguientes comandos:

    $ sudo apt-get install libbz2-dev zlib1g-dev libcppunit-dev libcurl4-gnutls-dev
    $ cd src/server/3rd-party/rocksdb
    $ make static_lib
    $ cd ../..
    $ cmake .

Para ejecutar las pruebas:

    $ make tests

Para compilar el servidor:

    $ make server

Para limpiar el proyecto:

<<<<<<< HEAD
    $ make clean
=======
Desde consola dirigirse a la carpeta del proyecto y ejecutar los siguientes comandos:

$ cd src/server/3rd-party/rocksdb
$ make static_lib
$ cd ../..
$ cmake .

Para ejecutar las pruebas:
$ make tests

Para compilar el servidor:
$ make server

Para limpiar el proyecto:
$ make clean
>>>>>>> dev
