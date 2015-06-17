#ifndef SENDMESSAGESERVICE_H_
#define SENDMESSAGESERVICE_H_

#include "ServiceInterface.h"
#include "../database/Database.h"
#include "../user/chat/Chat.h"
#include "../user/User.h"

class SendMessageService: public ServiceInterface {
public:
	/**
	 * Devuelve el nombre con el que se accederá al servicio
	 */
	virtual std::string getUri() const;
	/*
	 * Agrega mensaje a la lista de conversaciones
	 */
	virtual std::string executeRequest(const Json::Value &paramMap) const;
	Json::Value doSendMessage(const Json::Value &data) const;
private:
	static const std::string serviceName;
};

class SendMessageServiceCreator : public ServiceCreatorInterface{
public:
    virtual ServiceInterface* create(Database& userDb, Database& chatDb);
};

#endif /* SENDMESSAGESERVICE_H_ */
