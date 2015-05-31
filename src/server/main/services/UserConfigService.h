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
#include "utilities/LocationManager.h"

using namespace std;

class UserConfigService: public ServiceInterface {
	friend class UserConfigServiceTest;
public:

	std::string getUri() const;

	//Actualiza datos del user
	std::string executeRequest(const std::map<std::string, std::string> &paramMap) const;

private:

	static const std::string serviceName;

	static Json::Value doUserConfig(const Json::Value &data);
};

class UserConfigServiceCreator: public ServiceCreatorInterface{
	virtual ServiceInterface* create();
};

#endif /* SERVER_MAIN_SERVICES_USERCONFIGSERVICE_H_ */
