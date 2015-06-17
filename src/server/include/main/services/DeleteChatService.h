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
public:
	DeleteChatService(Database& userDb, Database& chatDb);
	virtual ~DeleteChatService();
	virtual std::string getUri() const;
	virtual std::string executeRequest(const Json::Value &paramMap) const;
	Json::Value doDeleteChat(const Json::Value &data) const;
private:
	static const std::string serviceName;
	/** Base de datos de usuarios **/
	Database& userDb;
	/** Base de datos de chats **/
	Database& chatDb;
};

class DeleteChatServiceCreator: public ServiceCreatorInterface{

	virtual ServiceInterface* create(Database& userDb, Database& chatDb);
};

#endif /* CURRENTCHATSSERVICE_H_ */
