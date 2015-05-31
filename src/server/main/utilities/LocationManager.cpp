/*
 * LocationManager.cpp
 *
 *  Created on: 31/5/2015
 *      Author: marian
 */

#include "LocationManager.h"

LocationManager::LocationManager() {}

LocationManager::~LocationManager() {}

std::string LocationManager::getLocation(int latitude, int longitude){
	return DEFAULT_USER_LOCATION;
}
