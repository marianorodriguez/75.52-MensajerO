/*
 * BroadcastService.h
 *
 *  Created on: 6/6/2015
 *      Author: marian
 */

#ifndef CODE_MAIN_SERVICES_BROADCASTSERVICE_H_
#define CODE_MAIN_SERVICES_BROADCASTSERVICE_H_

#include "ServiceInterface.h"
#include "SendMessageService.h"

class Database;

/**
 * Clase encargada de realizar el servicio de difusion de mensajes del servidor.
 * Un usuario que use este servicio le mandará un mensaje a todos los usuarios registrados en el servidor.
 */
class BroadcastService: public ServiceInterface {
public:
	BroadcastService(Database& userDb, Database& chatDb);
	virtual ~BroadcastService();
	virtual std::string getUri() const;
	virtual std::string executeRequest(const std::string &paramMap) const;
	/**
	 * Encargado de aplicar el servicio de difusion.
	 * @param data información de entrada del servicio.
	 * @return informacion sobre el resultado de la ejecucion del servicio.
	 */
	std::string doBroadcast(const std::string &data) const;

private:
	Database& userDb;
	Database& chatDb;
};

/**
 * Creator del servicio de difusion.
 */
class BroadcastServiceCreator: public ServiceCreatorInterface {
public:
    virtual ServiceInterface* create(Database& userDb, Database& chatDb);
};

#endif /* CODE_MAIN_SERVICES_BROADCASTSERVICE_H_ */
