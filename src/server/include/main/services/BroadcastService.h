/*
 * BroadcastService.h
 *
 *  Created on: 6/6/2015
 *      Author: marian
 */

#ifndef CODE_MAIN_SERVICES_BROADCASTSERVICE_H_
#define CODE_MAIN_SERVICES_BROADCASTSERVICE_H_

#include "ServiceInterface.h"
#include "../config.h"
#include "../database/Database.h"
#include "../user/chat/Chat.h"
#include "../user/User.h"

class BroadcastService: public ServiceInterface {
	friend class BroadcastServiceTest;
public:
	/**
	 * Devuelve el nombre con el que se accederá al servicio
	 */
	virtual std::string getUri() const;

	virtual std::string executeRequest(const Json::Value &paramMap) const;
private:
	static const std::string serviceName;
	static Json::Value doBroadcast(const Json::Value &data);
};

class BroadcastServiceCreator : public ServiceCreatorInterface{
public:
    virtual ServiceInterface* create();
};

#endif /* CODE_MAIN_SERVICES_BROADCASTSERVICE_H_ */
