/*
 * UserConfigService.h
 *
 *  Created on: 29/4/2015
 *      Author: marian
 */

#ifndef SERVER_MAIN_SERVICES_USERCONFIGSERVICE_H_
#define SERVER_MAIN_SERVICES_USERCONFIGSERVICE_H_

#include "services/ServiceInterface.h"
#include "config.h"

class UserConfigService: public ServiceInterface {
public:

	std::string getUri() const;
	void executeRequest(const Connection& connection) const;

private:

	static const std::string serviceName;
};

class UserConfigServiceCreator: public ServiceCreatorInterface{
	virtual ServiceInterface* create();
};

#endif /* SERVER_MAIN_SERVICES_USERCONFIGSERVICE_H_ */
