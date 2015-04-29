/*
 * ConnectionManager.cpp
 *
 *  Created on: 27/4/2015
 *      Author: marian
 */

#include <services/ConnectionManager.h>
#include <iostream>

int ConnectionManager::deltaTime = 2; //MIN DELTA == 2 TODO des-hardcodear
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

void ConnectionManager::destroyInstance(){
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
	running = true;
	pthread_create(&updateThread, NULL, runFunction, this);
}

void ConnectionManager::stopUpdating() {
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

	mtx.lock();
	connectedUsers[username] = time(0);
	mtx.unlock();
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
