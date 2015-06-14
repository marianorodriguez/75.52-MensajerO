#ifndef LOGINSERVICE_H_
#define LOGINSERVICE_H_
#include "ServiceInterface.h"
#include "../user/User.h"
#include "../database/Database.h"
#include "../utilities/LocationManager.h"

class LogInService: public ServiceInterface {
	friend class LogInServiceTest;
public:
	/**
	 * Devuelve el nombre del servicio: logIn
	 */
	virtual std::string getUri() const;

	virtual std::string executeRequest(const Json::Value &paramMap) const;
private:
	static const std::string serviceName;

	static Json::Value doLogIn(const Json::Value& data);
};

class LogInServiceCreator: public ServiceCreatorInterface{
	virtual ServiceInterface* create(Database& userDb, Database& chatDb);
};

#endif /* LOGINSERVICE_H_ */
