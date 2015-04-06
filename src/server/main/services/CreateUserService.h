#ifndef CREATE_USER_SERVICE_H
#define CREATE_USER_SERVICE_H
#include "ServiceInterface.h"

class CreateUserService : public ServiceInterface{
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
};

#endif // CREATE_USER_SERVICE_H
