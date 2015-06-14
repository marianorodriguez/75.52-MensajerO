#ifndef SIGNUP_SERVICE_H
#define SIGNUP_SERVICE_H
#include "ServiceInterface.h"
#include "../user/User.h"
#include "../database/Database.h"
#include "../utilities/LocationManager.h"

class SignUpService: public ServiceInterface {
public:
	SignUpService(Database& database);
	/**
	 * Devuelve el nombre del servicio: createUser
	 */
	virtual std::string getUri() const;
	/**
	 * Verifica que el usuario no exista y devuelve OK si pudo agregarlo.
	 */
	virtual std::string executeRequest(const Json::Value &paramMap) const;
	/**
	 * Valida si existe un usuario registrado con ese nombre
	 */
	bool checkUsernameExists(const std::string& username) const;
	Json::Value doSignUp(const Json::Value& data) const;
private:
	static const std::string serviceName;

	Database& userDb;

};

class SignUpServiceCreator : public ServiceCreatorInterface{
public:
	virtual ServiceInterface* create(Database& userDb, Database& chatDb);
};

#endif // SIGNUP_SERVICE_H
