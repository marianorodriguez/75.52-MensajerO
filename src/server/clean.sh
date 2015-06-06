
# NO borra las libs generadas de 3rd-party.

preguntar(){
mensaje=$1
aceptar=$2
rechazar=$3
		
	echo $mensaje
	while true
	do
		read respuesta

		if [ "$respuesta" = "$aceptar" ]
		then
			return 1
		elif [ "$respuesta" = "$rechazar" ]
		then
		    	return 0
		else
			echo "Por favor escriba '$aceptar' o '$rechazar'"
		fi
	done
}

preguntar "Desea borrar la base de datos del servidor?(si/no)" si no
borrarDB=$?

preguntar "Se procederá a limpiar el servidor, está seguro que desea continuar?(si/no)" si no
if [ $? -eq 1 ]
then
	if [ $borrarDB -eq 1 ]
	then
		echo "Borrando base de datos..."
		rm -rf database
	fi

	echo "Borrando archivos y carpetas autogeneradas..."
	rm -rf CMakeFiles
	rm -rf CMakeCache.txt
	rm -rf testResult.info
	rm -rf cmake_install.cmake
	rm -rf CTestTestfile.cmake
	rm -rf logging.txt
	rm -rf Makefile
	rm -rf Testing

	rm -rf code/main/CMakeFiles
	rm -rf code/main/cmake_install.cmake
	rm -rf code/main/Makefile
	rm -rf code/main/server
	rm -rf code/main/libmensajero-model.a

	rm -rf code/main/database/CMakeFiles
	rm -rf code/main/database/cmake_install.cmake
	rm -rf code/main/database/Makefile
	rm -rf code/main/database/libmensajero-database.a

	rm -rf code/main/services/CMakeFiles
	rm -rf code/main/services/cmake_install.cmake
	rm -rf code/main/services/Makefile
	rm -rf code/main/services/libmensajero-services.a

	rm -rf code/main/utilities/CMakeFiles
	rm -rf code/main/utilities/cmake_install.cmake
	rm -rf code/main/utilities/Makefile
	rm -rf code/main/utilities/libmensajero-utilities.a

	rm -rf code/tests/CMakeFiles
	rm -rf code/tests/cmake_install.cmake
	rm -rf code/tests/Makefile
	rm -rf code/tests/tests
	rm -rf code/tests/CTestTestfile.cmake

	rm -rf code/tests/rest-client/CMakeFiles
	rm -rf code/tests/rest-client/cmake_install.cmake
	rm -rf code/tests/rest-client/Makefile
	rm -rf code/tests/rest-client/librest-client.a

	rm -rf code/tests/services/CMakeFiles
	rm -rf code/tests/services/cmake_install.cmake
	rm -rf code/tests/services/Makefile
	rm -rf code/tests/services/libservice-test.a

else
	echo "Abortando..."
fi
