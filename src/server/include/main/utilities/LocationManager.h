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

class LocationManager {
	friend class LocationManagerTests;
public:
	LocationManager();
	virtual ~LocationManager();
	static std::string getLocation(const std::string &location);

private:
	static std::map<std::string, std::string> nodes;
	static std::string getNodeName(const std::string &location);
	static void parseLocation(const std::string &location, double &latitude, double &longitude);
	static std::string nearestNode(const std::string &location);
	static double distance(const std::string &location1, const std::string &location2);
};

#endif /* MAIN_UTILITIES_LOCATIONMANAGER_H_ */
