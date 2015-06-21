/*
 * LocationManager.cpp
 *
 *  Created on: 31/5/2015
 *      Author: marian
 */

#include "../../include/main/utilities/LocationManager.h"

std::map<std::string, std::string> LocationManager::nodes;
LocationManager* LocationManager::instance = 0;

LocationManager::LocationManager() {

	Json::Reader reader;
	Json::Value root;
	std::ifstream file("config/geolocation.json");
	reader.parse(file, root);
	root = root["nodes"];
	for (unsigned int i = 0; i < root.size(); i++) {
		Json::Value node = root[i];
		std::string name = node["name"].asString();
		Json::Value locations = node["location"];
		std::string dl = locations["DL"].asString();
		std::string ur = locations["UR"].asString();
		GeoNode geoNode(dl, ur);
		nodes[geoNode.serialize()] = name;
	}
}

LocationManager::~LocationManager() {
}

LocationManager* LocationManager::getInstance() {
	if(instance == 0){
		instance = new LocationManager();
	}
	return instance;
}

std::string LocationManager::getLocation(const std::string &location) {

	for (std::map<std::string, std::string>::iterator i = nodes.begin(); i != nodes.end();
			++i) {
		GeoNode node(i->first);
		if (node.inside(location)) {
			return i->second;
		}
	}
	return DEFAULT_USER_LOCATION;
}

GeoNode::GeoNode(std::string& dl, std::string& ur) {
	this->dl = dl;
	this->ur = ur;
}

GeoNode::GeoNode(const std::string &serialized) {

	int separator = serialized.find("#");
	this->dl = serialized.substr(0, separator);
	this->ur = serialized.substr(separator + 1, serialized.size());
}

bool GeoNode::inside(const std::string &location) const {

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

void GeoNode::parseLocation(const std::string &location, double& lat, double &lon) {
	int index = location.find(';');
	lat = atof(location.substr(0, index).c_str());
	lon = atof(location.substr(index + 1, location.size()).c_str());
}

std::string GeoNode::serialize() const {
	return (this->dl + "#" + this->ur);
}
