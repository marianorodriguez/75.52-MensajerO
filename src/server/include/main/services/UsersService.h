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
public:
	UsersService(Database& userDb);
	virtual std::string getUri() const;
	virtual std::string executeRequest(const std::string &paramMap) const;
	/**
	 * Aplica el servicio de listado de usuarios.
	 * @param data informacion de entrada para el servicio.
	 * @return listado con informacion de todos los usuarios registrados en el servidor.
	 */
	std::string doUsers(const std::string &data) const;
	
private:
	static const std::string serviceName;
	Database & userDb;
};

/**
 * creador del servicio de listado de usuarios.
 */
class UsersServiceCreator: public ServiceCreatorInterface {
	virtual ServiceInterface* create(Database& userDb, Database& chatDb);
};

#endif /* SERVER_MAIN_SERVICES_USERSSERVICE_H_ */
