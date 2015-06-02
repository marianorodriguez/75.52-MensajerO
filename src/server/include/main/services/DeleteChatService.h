/*
 * DeleteChatService.h
 *
 *  Created on: 30/5/2015
 *      Author: marian
 */

#ifndef MAIN_SERVICES_DELETECHATSERVICE_H_
#define MAIN_SERVICES_DELETECHATSERVICE_H_

#include "../config.h"
#include "../user/chat/Chat.h"
#include "../user/User.h"
#include "../database/Database.h"
#include "ServiceInterface.h"

class DeleteChatService: public ServiceInterface {
	friend class DeleteChatServiceTest;
public:

	virtual std::string getUri() const;

	virtual std::string executeRequest(const Json::Value &paramMap) const;
private:
	static const std::string serviceName;

	static Json::Value doDeleteChat(const Json::Value &data);
};

class DeleteChatServiceCreator: public ServiceCreatorInterface{

	virtual ServiceInterface* create();
};

#endif /* CURRENTCHATSSERVICE_H_ */
