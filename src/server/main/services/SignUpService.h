#ifndef SIGNUP_SERVICE_H
#define SIGNUP_SERVICE_H
#include "ServiceInterface.h"
#include "user/User.h"
#include "database/Database.h"

class SignUpService: public ServiceInterface {
	friend class ServicesIntegrationTests;
public:
	/**
	 * Devuelve el nombre del servicio: createUser
	 */
	virtual std::string getUri() const;
	/**
	 * Verifica que el usuario no exista y devuelve OK si pudo agregarlo.
	 */
	virtual void executeRequest(const Connection& connection) const;
private:
	static const std::string serviceName;

	bool checkUsernameExists(const std::string& username,
			const Connection& connection) const;
};

class SignUpServiceCreator : public ServiceCreatorInterface{
public:
    virtual ServiceInterface* create();
};

#endif // SIGNUP_SERVICE_H
