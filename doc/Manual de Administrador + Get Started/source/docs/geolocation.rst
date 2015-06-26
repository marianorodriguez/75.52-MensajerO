.. index:: Geolocalización

Geolocalización.
****************

Aparte del archivo *config.json*, en la carpeta config del servidor también estará el archivo *geolocation.json*, con el siguiente contenido::

	{
		"nodes": [
			{"name": "San Telmo", "location": {"DL":"-34.622667;-58.380351", "UR":"-34.612213;-58.365888"}},
			{"name": "Monserrat", "location": {"DL":"-34.612213;-58.386359", "UR":"-34.608858;-58.365888"}},
			{"name": "San Nicolas", "location": {"DL":"-34.608858;-58.386359", "UR":"-34.598578;-58.367476"}},
			{"name": "Retiro", "location": {"DL":"-34.598578;-58.382539", "UR":"-34.588687;-58.367476"}},
			{"name": "Palermo", "location": {"DL":"-34.597968;-58.428260", "UR":"-34.587475;-58.407017"}}		
		]
	}

Este archivo sirve para registrar barrios dentro del servicio de geolocalización del servidor.
Para agregar un nuevo barrio, habrá que agregar una nueva linea con el nombre del barrio, y la latitud y longitud de las esquinas inferior izquierda (DL) y superior derecha (UR), considerando que el barrio tiene forma de rectangulo.

Tené en cuenta que si probás esta funcionalidad en un barrio que no está listado en este archivo, el localizador no podrá reconocer la zona y te indicará "CABA" como ubicación predeterminada.
