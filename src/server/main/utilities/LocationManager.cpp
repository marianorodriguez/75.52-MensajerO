/*
 * LocationManager.cpp
 *
 *  Created on: 31/5/2015
 *      Author: marian
 */

#include "LocationManager.h"

LocationManager::LocationManager() {}

LocationManager::~LocationManager() {}

std::string LocationManager::getLocation(std::string location) {

	float longitude, latitude;
	parseLocation(location, latitude, longitude);
	return DEFAULT_USER_LOCATION;
}

void LocationManager::parseLocation(const string &location, float &latitude,
		float &longitude) {
	int separator = location.find(',');
	latitude = atof(location.substr(0, separator).c_str());
	longitude = atof(location.substr(separator + 1, location.size()).c_str());
}
