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

class GeoNode {
	friend class LocationManager;
	friend class LocationManagerTests;
public:
	GeoNode(std::string dl, std::string ur);
	GeoNode(const string &serialized);
	bool inside(const std::string &location) const;
private:
	std::string ur;
	std::string dl;

	static void parseLocation(const std::string &location, double &lat, double &lon);
	string serialize() const;
};

class LocationManager {
	friend class LocationManagerTests;
public:
	virtual ~LocationManager();
	static LocationManager* getInstance();
	static std::string getLocation(const std::string &location);

private:
	LocationManager();
	static LocationManager* instance;
	static map<string, string> nodes;
};


#endif /* MAIN_UTILITIES_LOCATIONMANAGER_H_ */
