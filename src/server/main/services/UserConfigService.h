/*
 * UserConfigService.h
 *
 *  Created on: 29/4/2015
 *      Author: marian
 */

#ifndef SERVER_MAIN_SERVICES_USERCONFIGSERVICE_H_
#define SERVER_MAIN_SERVICES_USERCONFIGSERVICE_H_

#include "services/ServiceInterface.h"
#include "../database/Database.h"
#include "../user/User.h"
#include "config.h"

using namespace std;

class UserConfigService: public ServiceInterface {
public:

	std::string getUri() const;

	//Actualiza datos del user
	void executeRequest(const Connection& connection) const;

private:

	static const std::string serviceName;
};

class UserConfigServiceCreator: public ServiceCreatorInterface{
	virtual ServiceInterface* create();
};

#endif /* SERVER_MAIN_SERVICES_USERCONFIGSERVICE_H_ */
