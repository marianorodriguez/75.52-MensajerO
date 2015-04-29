/*
 * ImAliveService.h
 *
 *  Created on: 29/4/2015
 *      Author: marian
 */

#ifndef SERVER_MAIN_SERVICES_IMALIVESERVICE_H_
#define SERVER_MAIN_SERVICES_IMALIVESERVICE_H_

#include "services/ConnectionManager.h"
#include "ServiceInterface.h"
#include "config.h"

class ImAliveService: public ServiceInterface {
public:
	ImAliveService();
	virtual ~ImAliveService();

	std::string getUri() const;
	void executeRequest(const Connection& connection) const;

private:

	static const std::string serviceName;
};

class ImAliveServiceCreator: public ServiceCreatorInterface{
public:
	virtual ServiceInterface* create();
};

#endif /* SERVER_MAIN_SERVICES_IMALIVESERVICE_H_ */
