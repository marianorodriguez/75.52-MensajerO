/*
 * UserConfigService.h
 *
 *  Created on: 29/4/2015
 *      Author: marian
 */

#ifndef SERVER_MAIN_SERVICES_USERCONFIGSERVICE_H_
#define SERVER_MAIN_SERVICES_USERCONFIGSERVICE_H_

#include "../services/ServiceInterface.h"
#include "../database/Database.h"
#include "../user/User.h"
#include "../config.h"
#include "../utilities/LocationManager.h"

using namespace std;

/**
 * Clase encargada de realizar el servicio de actualizacion de usuarios del servidor.
 * El usuario que use este servicio podrá actualizar su informacion personal.
 */
class UserConfigService: public ServiceInterface {
public:
	std::string getUri() const;
	std::string executeRequest(const Json::Value &paramMap) const;
	/**
	 * Aplica el servicio de configuracion de un usuario.
	 * @param data informacion actualizada de un usuario.
	 * @return informacion sobre el resultado del servicio.
	 */
	Json::Value doUserConfig(const Json::Value &data) const;

private:
	static const std::string serviceName;
};

/**
 * Creador del servicio de actualizacion del usuario.
 */
class UserConfigServiceCreator: public ServiceCreatorInterface{
	virtual ServiceInterface* create(Database& userDb, Database& chatDb);
};

#endif /* SERVER_MAIN_SERVICES_USERCONFIGSERVICE_H_ */
