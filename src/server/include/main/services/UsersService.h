#ifndef SERVER_MAIN_SERVICES_USERSSERVICE_H_
#define SERVER_MAIN_SERVICES_USERSSERVICE_H_

#include "../services/ServiceInterface.h"
#include "../database/Database.h"
#include "../user/User.h"
#include "../config.h"

/**
 * Clase encargada de realizar el servicio de listar usuarios del servidor.
 * El usuario que use este servicio obtendrá un listado con información sobre todos los usuarios registrados en el servidor.
 */
class UsersService: public ServiceInterface {
	friend class UsersServiceTest;
public:
	virtual std::string getUri() const;
	virtual std::string executeRequest(const Json::Value &paramMap) const;

private:
	/**
	 * Aplica el servicio de listado de usuarios.
	 * @param data informacion de entrada para el servicio.
	 * @return listado con informacion de todos los usuarios registrados en el servidor.
	 */
	static Json::Value doUsers(const Json::Value &data);

};

/**
 * creador del servicio de listado de usuarios.
 */
class UsersServiceCreator: public ServiceCreatorInterface {
	virtual ServiceInterface* create();
};

#endif /* SERVER_MAIN_SERVICES_USERSSERVICE_H_ */
