/*
 * LocationManager.cpp
 *
 *  Created on: 31/5/2015
 *      Author: marian
 */

#include "../../include/main/utilities/LocationManager.h"

LocationManager::LocationManager() {

//	ifstream file;
//	file.open("config/geolocation.json"); //TODO deshardcodear
//
//	file.read()
//	JsonMap json("hola");
//	this->nodes = json.getMap();
}

LocationManager::~LocationManager() {}

std::string LocationManager::getLocation(std::string location) {

	float longitude, latitude;
	parseLocation(location, latitude, longitude);
	return nearestLocation(latitude, longitude);
}

void LocationManager::parseLocation(const string &location, float &latitude,
		float &longitude) {
	int separator = location.find(';');
	latitude = atof(location.substr(0, separator).c_str());
	longitude = atof(location.substr(separator + 1, location.size()).c_str());
}

std::string LocationManager::nearestLocation(const float &lat, const float &lon){

	return DEFAULT_USER_LOCATION;
}
