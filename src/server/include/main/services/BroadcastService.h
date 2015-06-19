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
#include "../config.h"
#include "../database/Database.h"
#include "../user/chat/Chat.h"
#include "../user/User.h"

/**
 * Clase encargada de realizar el servicio de difusion de mensajes del servidor.
 * Un usuario que use este servicio le mandará un mensaje a todos los usuarios registrados en el servidor.
 */
class BroadcastService: public ServiceInterface {
	friend class BroadcastServiceTest;
public:
	virtual std::string getUri() const;
	virtual std::string executeRequest(const Json::Value &paramMap) const;

private:

	/**
	 * Encargado de aplicar el servicio de difusion.
	 * @param data información de entrada del servicio.
	 * @return informacion sobre el resultado de la ejecucion del servicio.
	 */
	static Json::Value doBroadcast(const Json::Value &data);
};

/**
 * Creator del servicio de difusion.
 */
class BroadcastServiceCreator: public ServiceCreatorInterface {
public:
	virtual ServiceInterface* create();
};

#endif /* CODE_MAIN_SERVICES_BROADCASTSERVICE_H_ */
