75.52-MensajerO


Taller de Programacion II


### Documentación

Además de este Readme, se encuentra documentación en formato restructured text, en el directorio *doc/informe*.

Para compilar el documento, desde la consola dirigirse a esta carpeta y ejecutar:

	$ make html

Para luego ver el informe, abrir el archivo *doc/informe/_build/html/index.html*
La documentación fue generada con sphinx-doc.

### Compilación

Desde consola dirigirse a la carpeta del proyecto y ejecutar los siguientes comandos:

Instalar dependencias

    $ sudo apt-get install libbz2-dev zlib1g-dev libcppunit-dev libcurl4-gnutls-dev lcov

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

### Scripts prearmados

Para facilitar la instalación de la aplicación, se armaron algunos scripts en bash que agrupan varios de los comandos detallados abajo.

**build.sh** : Compila la aplicación en una carpeta llamada *build*, y copia en su interior a *run.sh*, *runTests.sh*, *coverage.sh*. Además, si se le agrega el parametro "coverage" compila con soporte para pruebas de cobertura.

**run.sh** : Ejecuta el servidor, y crea una carpeta para las bases de datos si es necesario.

**runTests.sh** : Ejecuta las pruebas, limpiando los contenidos creados por pruebas anteriores, 

**coverage.sh** : Ejecuta las pruebas y recolecta los datos de los tests de coverage.

**clean.sh** : Limpia los archivos generados por CMake y Makefile, dando además la opción de borrar la base de datos.

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


