/*
 * ConnectionManager.cpp
 *
 *  Created on: 27/4/2015
 *      Author: marian
 */

#include "../../include/main/services/ConnectionManager.h"
#include "../../include/main/config.h"
#include "../../include/main/user/User.h"

const int ConnectionManager::deltaTime = 2; //MIN DELTA == 2 TODO des-hardcodear
ConnectionManager* ConnectionManager::managerInstance = NULL;
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
	this->updateThread = 0;
	this->running = false;
}

ConnectionManager::~ConnectionManager() {
}

void ConnectionManager::startUpdating() {
	running = true;
	pthread_create(&updateThread, NULL, runFunction, this);
}

void ConnectionManager::stopUpdating() {
	running = false;
	pthread_join(updateThread, NULL);
}

void* ConnectionManager::runFunction(void* args) {
	ConnectionManager* manager = static_cast<ConnectionManager*>(args);
	while (manager->running) {
		usleep(1000);
		manager->updateConnection();
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
	std::vector<std::string> key;
	key.push_back(username);
	try {
		User user(this->userDb->read(key));
	if(user.getStatus() != "offline") {
		user.setLastTimeConnected();
		this->userDb->write(key, user.serialize());
	}
	}catch(KeyNotFoundException &e){}

	connectedUsers[username] = time(0);
}

void ConnectionManager::setDatabase(Database* userDb){
	this->userDb = userDb;
}

void ConnectionManager::updateConnection() {
	std::vector<std::string> disconnectedUsers;

	for (std::map<std::string, int>::iterator it = connectedUsers.begin();
			it != connectedUsers.end(); ++it) {
		if (time(0) - it->second > deltaTime) {
			//el usuario se desconectó, lo saco del map
			disconnectedUsers.push_back(it->first);
		}
	}

	for (unsigned int i = 0; i < disconnectedUsers.size(); i++) {
		connectedUsers.erase(disconnectedUsers.at(i));
	}
}
