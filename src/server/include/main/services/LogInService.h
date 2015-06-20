#ifndef LOGINSERVICE_H_
#define LOGINSERVICE_H_
#include "ServiceInterface.h"
#include "../user/User.h"
#include "../database/Database.h"
#include "../utilities/LocationManager.h"
#include "../utilities/Random.h"

/**
 * Clase encargada de proveer el servicio de inicio de sesion en el servidor.
 * El usuario que use este servicio ganará acceso al resto de los servicios que invoque.
 */
class LogInService: public ServiceInterface {
	friend class LogInServiceTest;
public:
	virtual std::string getUri() const;
	virtual std::string executeRequest(const Json::Value &paramMap) const;

private:
	/**
	 * Aplica el servicio de inicio de sesion del servidor.
	 * @param data informacion de entrada.
	 * @return informacion sobre el resultado de la operación.
	 */
	static Json::Value doLogIn(const Json::Value& data);
};

/**
 * Creador del servicio de inicio de sesion del servidor.
 */
class LogInServiceCreator: public ServiceCreatorInterface {
	virtual ServiceInterface* create();
};

#endif /* LOGINSERVICE_H_ */
