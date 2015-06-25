.. index:: Pruebas

Pruebas
******
Para probar las distintas clases del servidor se utilizó **cppunit** donde se realizaron pruebas unitarias para comprobar el funcionamiento correcto de cada clase cubriendo la mayor cantidad de código posible. 
Para correr las pruebas es necesario correr los siguientes comandos::

	$ ./build.sh

	$ ./runTests.sh

Si se quieren correr con coverage se puede agregar un flag al script build::

	$ ./build.sh coverage
	
	$ ./coverage.sh

Esto luego abrirá una paǵina html donde se pueden observar los siguientes resultados. 


.. figure::  images/Coverage.png
   :target:  ../_images/Coverage.png
   :align:   center
