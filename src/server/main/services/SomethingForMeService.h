#ifndef SOMETHINGFORMESERVICE_H_
#define SOMETHINGFORMESERVICE_H_
#include "ServiceInterface.h"
#include "user/User.h"
#include "user/chat/Chat.h"
#include "database/Database.h"

class SomethingForMeService: public ServiceInterface {
	friend class SomethingForMeServiceTest;
public:
	/**
	* Devuelve el nombre del servicio: somethingForMe
	*/
	virtual std::string getUri() const;
	/**
	* Se fija si hay mensajes nuevos para el usuario
	*/
	virtual void executeRequest(const Connection& connection) const;
private:
	static const std::string serviceName;

	static Json::Value doSomethingForMe(const Json::Value &data);
};

class SomethingForMeServiceCreator: public ServiceCreatorInterface{
	virtual ServiceInterface* create();
};

#endif /* SOMETHINGFORMESERVICE_H_ */
