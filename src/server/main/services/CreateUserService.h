#ifndef CREATE_USER_SERVICE_H
#define CREATE_USER_SERVICE_H
#include "ServiceInterface.h"
#include "user/User.h"
#include "database/Database.h"

class CreateUserService: public ServiceInterface {
	friend class CreateUserServiceTest;
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

	void checkValidUsername(const std::string& username,
			const Connection& connection, bool& error) const;
	void checkusernameExists(const std::string& username,
			const Connection& connection, bool& error) const;
};

#endif // CREATE_USER_SERVICE_H
