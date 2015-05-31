/*
 * LocationManager.h
 *
 *  Created on: 31/5/2015
 *      Author: marian
 */

#ifndef MAIN_UTILITIES_LOCATIONMANAGER_H_
#define MAIN_UTILITIES_LOCATIONMANAGER_H_

#include "config.h"

class LocationManager {
public:
	LocationManager();
	virtual ~LocationManager();

	static std::string getLocation(int latitude, int longitude);
};

#endif /* MAIN_UTILITIES_LOCATIONMANAGER_H_ */
