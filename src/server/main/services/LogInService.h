#ifndef LOGINSERVICE_H_
#define LOGINSERVICE_H_
#include "ServiceInterface.h"
#include "user/User.h"
#include "database/Database.h"

class LogInService: public ServiceInterface {
public:
	/**
	 * Devuelve el nombre del servicio: logIn
	 */
	virtual std::string getUri() const;
	/**
	 * Verifica que el usuario exista y devuelve OK si existe.
	 */
	virtual void executeRequest(const Connection& connection) const;
private:
	static const std::string serviceName;
};

#endif /* LOGINSERVICE_H_ */
