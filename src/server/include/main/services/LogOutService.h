#ifndef LOGOUTSERVICE_H_
#define LOGOUTSERVICE_H_
#include "ServiceInterface.h"
#include "../user/User.h"
#include "../database/Database.h"

/**
 * Clase encargada de proveer el servicio de cierre de sesion en el servidor.
 * El usuario que use este servicio cerrará su sesión, permitiendole abrirla desde otro dispositivo.
 */
class LogOutService: public ServiceInterface {
	friend class LogInServiceTest;
public:
	virtual std::string getUri() const;
	virtual std::string executeRequest(const Json::Value &paramMap) const;

private:
	/**
	 * Aplica el servicio de cierre de sesion del servidor.
	 * @param data informacion de entrada.
	 * @return informacion sobre el resultado de la operación.
	 */
	static Json::Value doLogOut(const Json::Value& data);
};

/**
 * Creador del servicio de cierre de sesion del servidor.
 */
class LogOutServiceCreator: public ServiceCreatorInterface {
	virtual ServiceInterface* create();
};

#endif /* LOGOUTSERVICE_H_ */
