#ifndef SOMETHINGFORMESERVICE_H_
#define SOMETHINGFORMESERVICE_H_
#include "ServiceInterface.h"
#include "../user/User.h"
#include "../user/chat/Chat.h"
#include "../database/Database.h"

class SomethingForMeService: public ServiceInterface {
public:
	/**
	* Devuelve el nombre del servicio: somethingForMe
	*/
	virtual std::string getUri() const;
	virtual std::string executeRequest(const Json::Value &paramMap) const;
	/**
	* Se fija si hay mensajes nuevos para el usuario
	*/
	Json::Value doSomethingForMe(const Json::Value &data) const;

private:
	static const std::string serviceName;
};

class SomethingForMeServiceCreator: public ServiceCreatorInterface{
	virtual ServiceInterface* create(Database& userDb, Database& chatDb);
};

#endif /* SOMETHINGFORMESERVICE_H_ */
