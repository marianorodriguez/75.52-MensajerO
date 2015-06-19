/*
 * LocationManager.h
 *
 *  Created on: 31/5/2015
 *      Author: marian
 */

#ifndef MAIN_UTILITIES_LOCATIONMANAGER_H_
#define MAIN_UTILITIES_LOCATIONMANAGER_H_

#include "../config.h"
#include "json/json.h"
#include <map>
#include <fstream>
#include <math.h>

/**
 * Define un nodo del geolocalizador.
 */
class GeoNode {
	friend class LocationManager;
	friend class LocationManagerTests;
public:
	GeoNode(std::string dl, std::string ur);
	GeoNode(const string &serialized);

	/**
	 * Devuelve true si @param location está dentro de este nodo.
	 */
	bool inside(const std::string &location) const;
private:
	std::string ur;
	std::string dl;

	/**
	 * Convierte @param location en valores numericos de latitud y longitud.
	 */
	static void parseLocation(const std::string &location, double &lat,
			double &lon);
	string serialize() const;
};

/**
 * Clase encargada de procesar informacion de latitud y longitud para devolver el nombre del barrio a donde apuntan esas coordenadas.
 */
class LocationManager {
	friend class LocationManagerTests;
public:
	virtual ~LocationManager();
	static LocationManager* getInstance();

	/**
	 * Devuelve el nombre del barrio al que apunta @param location
	 */
	static std::string getLocation(const std::string &location);

private:
	LocationManager();
	static LocationManager* instance;
	static map<string, string> nodes;
};

#endif /* MAIN_UTILITIES_LOCATIONMANAGER_H_ */
