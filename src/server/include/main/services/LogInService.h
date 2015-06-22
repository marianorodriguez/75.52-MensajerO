#ifndef LOGINSERVICE_H_
#define LOGINSERVICE_H_
#include "ServiceInterface.h"
#include "../user/User.h"
#include "../utilities/LocationManager.h"

class Database;

/**
 * Clase encargada de proveer el servicio de inicio de sesion en el servidor.
 * El usuario que use este servicio ganará acceso al resto de los servicios que invoque.
 */
class LogInService: public ServiceInterface {
public:
	LogInService(Database& userDb);
	virtual ~LogInService();
	virtual std::string getUri() const;
	virtual std::string executeRequest(const Json::Value &paramMap) const;
	/**
	 * Aplica el servicio de inicio de sesion del servidor.
	 * @param data informacion de entrada.
	 * @return informacion sobre el resultado de la operación.
	 */
	Json::Value doLogIn(const Json::Value& data) const;

private:
	static const std::string serviceName;
	Database& userDb;
};

/**
 * Creador del servicio de inicio de sesion del servidor.
 */
class LogInServiceCreator: public ServiceCreatorInterface{
	virtual ServiceInterface* create(Database& userDb, Database& chatDb);
};

#endif /* LOGINSERVICE_H_ */
