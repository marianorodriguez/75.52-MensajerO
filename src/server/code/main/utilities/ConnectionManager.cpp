/*
 * ConnectionManager.cpp
 *
 *  Created on: 27/4/2015
 *      Author: marian
 */

#include "../../../include/main/utilities/ConnectionManager.h"

#include <iostream>
#include "../../include/main/config.h"
#include "../../include/main/user/User.h"

bool ConnectionManager::running = false;
std::map<std::string, int> ConnectionManager::connectedUsers;
ConnectionManager* ConnectionManager::managerInstance = NULL;
Mutex ConnectionManager::mtx;
Mutex ConnectionManager::constructorMutex;

ConnectionManager* ConnectionManager::getInstance() {

	if (!managerInstance) {
		constructorMutex.lock();
		if (!managerInstance) {
			managerInstance = new ConnectionManager();
		}
		constructorMutex.unlock();
	}
	return managerInstance;
}

void ConnectionManager::destroyInstance() {
	constructorMutex.lock();
	delete managerInstance;
	managerInstance = NULL;
	constructorMutex.unlock();
}

ConnectionManager::ConnectionManager() {
	connectedUsers.clear();
	this->updateThread = 0;
}

ConnectionManager::~ConnectionManager() {
}

void ConnectionManager::startUpdating() {
	Logger::getLogger()->write(Logger::DEBUG,
			"Starting connection manager...");
	running = true;
	pthread_create(&updateThread, NULL, runFunction, this);
}

void ConnectionManager::stopUpdating() {
	Logger::getLogger()->write(Logger::DEBUG,
			"Stopping connection manager...");
	running = false;
	pthread_join(updateThread, NULL);
}

void* ConnectionManager::runFunction(void* args) {

	while (running) {
		usleep(1000);
		mtx.lock();
		updateConnection();
		mtx.unlock();
	}
	return NULL;
}

std::vector<std::string> ConnectionManager::getConnectedUsers() {

	std::vector<std::string> usernames;
	mtx.lock();
	for (std::map<std::string, int>::iterator iter = connectedUsers.begin();
			iter != connectedUsers.end(); ++iter) {

		usernames.push_back(iter->first);
	}
	mtx.unlock();

	return usernames;
}

void ConnectionManager::updateUser(const std::string username) {

	//tengo que abrir el user, si status != offline , le actualizo el lastTime
	Database DB(DATABASE_USERS_PATH);
	std::vector<std::string> key;
	key.push_back(username);
	try {
		User user(DB.read(key));
		if (user.getStatus() != "offline") {
			user.setLastTimeConnected();
		}
		DB.write(key, user.serialize());
	} catch (KeyNotFoundException &e) {
	}

	mtx.lock();
	connectedUsers[username] = time(0);
	mtx.unlock();
}

void ConnectionManager::updateConnection() {

	std::vector<std::string> disconnectedUsers;

	for (std::map<std::string, int>::iterator it = connectedUsers.begin();
			it != connectedUsers.end(); ++it) {

		if (time(0) - it->second > MAXIMUM_IDLE_TIME) {
			//el usuario se desconectó, lo saco del map
			disconnectedUsers.push_back(it->first);
		}
	}

	for (unsigned int i = 0; i < disconnectedUsers.size(); i++) {
		Logger::getLogger()->write(Logger::DEBUG,
				disconnectedUsers.at(i)+" has disconnected.");
		connectedUsers.erase(disconnectedUsers.at(i));
	}
}
