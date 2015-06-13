/*
 * LocationManager.cpp
 *
 *  Created on: 31/5/2015
 *      Author: marian
 */

#include "../../include/main/utilities/LocationManager.h"

map<string, string> LocationManager::nodes;

LocationManager::LocationManager() {

	Json::Reader reader;
	Json::Value root;
	ifstream file("config/geolocation.json");
	reader.parse(file, root);
	root = root["nodes"];
	for (unsigned int i = 0; i < root.size(); i++) {
		Json::Value node = root[i];
		std::string name = node["name"].asString();
		Json::Value locations = node["location"];
		GeoNode geoNode(locations["DL"].asString(), locations["UR"].asString());
		nodes[geoNode.serialize()] = name;
	}
}

LocationManager::~LocationManager() {
}

std::string LocationManager::getLocation(const std::string &location) {

	for (map<string, string>::iterator i = nodes.begin(); i != nodes.end();
			++i) {
		GeoNode node(i->first);
		if (node.inside(location)) {
			return i->second;
		}
	}
	return DEFAULT_USER_LOCATION;
}

GeoNode::GeoNode(std::string dl, std::string ur) {
	this->dl = dl;
	this->ur = ur;
}

GeoNode::GeoNode(const string &serialized) {

	int separator = serialized.find("#");
	this->dl = serialized.substr(0, separator);
	this->ur = serialized.substr(separator + 1, serialized.size());
}

bool GeoNode::inside(const string &location) const {

	double latLoc, longLoc, latDL, longDL, latUR, longUR;
	parseLocation(location, latLoc, longLoc);
	parseLocation(this->ur, latUR, longUR);
	parseLocation(this->dl, latDL, longDL);

	if (latDL < latLoc && latLoc < latUR) {
		if (longDL < longLoc && longLoc < longUR) {
			return true;
		}
	}
	return false;
}

void GeoNode::parseLocation(const string &location, double &lat, double &lon) {
	int index = location.find(';');
	lat = atof(location.substr(0, index).c_str());
	lon = atof(location.substr(index + 1, location.size()).c_str());
}

string GeoNode::serialize() const {
	return (this->dl + "#" + this->ur);
}
