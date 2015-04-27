/*
 * ConnectionManager.h
 *
 *  Created on: 27/4/2015
 *      Author: marian
 */

#ifndef SERVER_MAIN_SERVICES_CONNECTIONMANAGER_H_
#define SERVER_MAIN_SERVICES_CONNECTIONMANAGER_H_

#include <map>
#include <unistd.h>

class ConnectionManager {
	friend class ConnectionManagerTest;

public:
	ConnectionManager();
	virtual ~ConnectionManager();
	void updateConnection();
	void updateUser(const std::string username);


private:

	std::map<std::string, int> connectedUsers;
	std::map<std::string, int>::iterator it;
	int deltaTime;
};

#endif /* SERVER_MAIN_SERVICES_CONNECTIONMANAGER_H_ */
