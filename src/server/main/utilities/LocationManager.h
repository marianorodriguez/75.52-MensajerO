/*
 * LocationManager.h
 *
 *  Created on: 31/5/2015
 *      Author: marian
 */

#ifndef MAIN_UTILITIES_LOCATIONMANAGER_H_
#define MAIN_UTILITIES_LOCATIONMANAGER_H_

#include "config.h"
#include <map>

class LocationManager {
public:
	LocationManager();
	virtual ~LocationManager();
	static std::string getLocation(std::string location);

private:
	std::map<std::string, std::string> nodes;
	static void parseLocation(const std::string &location, float &latitude, float &longitude);
};

#endif /* MAIN_UTILITIES_LOCATIONMANAGER_H_ */
