/*
 * ConnectionManager.h
 *
 *  Created on: 27/4/2015
 *      Author: marian
 */

#ifndef SERVER_MAIN_SERVICES_CONNECTIONMANAGER_H_
#define SERVER_MAIN_SERVICES_CONNECTIONMANAGER_H_

#include <map>
#include <vector>
#include <thread>
#include <unistd.h>
#include "utilities/Mutex.h"

class ConnectionManager{
	friend class ConnectionManagerTest;

public:
	ConnectionManager();
	virtual ~ConnectionManager();

	void startUpdating();
	std::vector<std::string> getConnectedUsers();
	void updateUser(const std::string username);
	void stopUpdating();

private:
	static void updateConnection();

	static void* runFunction(void* args);

	static Mutex mtx;
	pthread_t updateThread;
	static std::map<std::string, int> connectedUsers;
	std::map<std::string, int>::iterator it;
	static int deltaTime;
	static bool running;
};

#endif /* SERVER_MAIN_SERVICES_CONNECTIONMANAGER_H_ */
