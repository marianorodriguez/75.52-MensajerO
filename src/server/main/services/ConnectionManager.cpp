/*
 * ConnectionManager.cpp
 *
 *  Created on: 27/4/2015
 *      Author: marian
 */

#include <services/ConnectionManager.h>

ConnectionManager::ConnectionManager() {
	this->connectedUsers.clear();
	this->deltaTime = 2;
}

ConnectionManager::~ConnectionManager() {
}

void ConnectionManager::updateUser(const std::string username) {

	this->connectedUsers[username] = time(0);
}

void ConnectionManager::updateConnection() {

	int lastTimeConnected;

	for (std::map<std::string, int>::iterator it = connectedUsers.begin();
			it != connectedUsers.end(); ++it) {

		lastTimeConnected = it->second;

		if (time(0) - lastTimeConnected > deltaTime) {
			//el usuario se desconectó, lo saco del map
			this->connectedUsers.erase(it->first);

		} else {
			//actualizo al usuario
			this->connectedUsers[it->first] = time(0);
		}
	}
}
