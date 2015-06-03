#ifndef SIGNUP_SERVICE_H
#define SIGNUP_SERVICE_H
#include "ServiceInterface.h"
#include "../user/User.h"
#include "../database/Database.h"
#include "../utilities/LocationManager.h"

class SignUpService: public ServiceInterface {
	friend class SignUpServiceTest;
public:
	/**
	 * Devuelve el nombre del servicio: createUser
	 */
	virtual std::string getUri() const;
	/**
	 * Verifica que el usuario no exista y devuelve OK si pudo agregarlo.
	 */
	virtual std::string executeRequest(const Json::Value &paramMap) const;
private:
	static const std::string serviceName;

	static Json::Value doSignUp(const Json::Value& data);

};

class SignUpServiceCreator : public ServiceCreatorInterface{
public:
    virtual ServiceInterface* create();
};

#endif // SIGNUP_SERVICE_H
