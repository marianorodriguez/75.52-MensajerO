#ifndef CREATE_USER_SERVICE_H
#define CREATE_USER_SERVICE_H
#include "ServiceInterface.h"
#include "user/User.h"
#include "database/Database.h"

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
	virtual void executeRequest(const Connection& connection) const;
private:
	static const std::string serviceName;

	void checkusernameExists(const std::string& username,
			const Connection& connection, bool& error) const;
};

#endif // CREATE_USER_SERVICE_H
