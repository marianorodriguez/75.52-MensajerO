/*
 * LocationManager.cpp
 *
 *  Created on: 31/5/2015
 *      Author: marian
 */

#include "../../include/main/utilities/LocationManager.h"
#include <istream>

std::map<std::string, std::string> LocationManager::nodes;
double LocationManager::NODE_RADIUS;

LocationManager::LocationManager() {

	Json::Reader reader;
	Json::Value root;
	std::ifstream file("config/geolocation.json");
	reader.parse(file, root);
	NODE_RADIUS = atof(root["node_radius"].asString().c_str());
	root = root["nodes"];
	for (unsigned int i = 0; i < root.size(); i++) {
		Json::Value node = root[i];
		std::string name = node["name"].asString();
		Json::Value locations = node["location"];
		for (unsigned int j = 0; j < locations.size(); j++) {
			nodes[locations[j]["latLong"].asString()] = name;
		}
	}
}

LocationManager::~LocationManager() {
	nodes.clear();
}

std::string LocationManager::getLocation(const std::string &location) {

	std::string nearest = nearestNode(location);
	if (distance(nearest, location) <= NODE_RADIUS) {
		return getNodeName(nearest);
	} else {
		return DEFAULT_USER_LOCATION;
	}
}

std::string LocationManager::getNodeName(const std::string &location) {
	std::map<std::string, std::string>::iterator pos = nodes.find(location);
	if (pos != nodes.end())
		return nodes.at(location);
	else
		return DEFAULT_USER_LOCATION;
}

double LocationManager::distance(const std::string &location1,
		const std::string &location2) {

	double lat1, long1, lat2, long2;
	parseLocation(location1, lat1, long1);
	parseLocation(location2, lat2, long2);
	return sqrt(
			(lat1 - lat2) * (lat1 - lat2) + (long1 - long2) * (long1 - long2));
}

void LocationManager::parseLocation(const std::string &location, double &latitude,
		double &longitude) {
	int separator = location.find(';');
	latitude = atof(location.substr(0, separator).c_str());
	longitude = atof(location.substr(separator + 1, location.size()).c_str());
}

std::string LocationManager::nearestNode(const std::string &location) {

	std::string nearest = "0;0";
	for (std::map<std::string, std::string>::iterator i = nodes.begin();
			i != nodes.end(); ++i) {

		if (distance(location, i->first) <= distance(location, nearest))
			nearest = i->first;
	}
	return nearest;
}
