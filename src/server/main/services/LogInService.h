#ifndef LOGINSERVICE_H_
#define LOGINSERVICE_H_
#include "ServiceInterface.h"
#include "user/User.h"
#include "database/Database.h"

class LogInService: public ServiceInterface {
	friend class LogInServiceTest;
public:
	/**
	 * Devuelve el nombre del servicio: logIn
	 */
	virtual std::string getUri() const;

	virtual std::string executeRequest(const std::map<std::string, std::string> &paramMap) const;
private:
	static const std::string serviceName;

	static Json::Value doLogIn(const Json::Value& data);
};

class LogInServiceCreator: public ServiceCreatorInterface{
	virtual ServiceInterface* create();
};

#endif /* LOGINSERVICE_H_ */
