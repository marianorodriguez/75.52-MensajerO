/*
 * DeleteChatService.h
 *
 *  Created on: 30/5/2015
 *      Author: marian
 */

#ifndef MAIN_SERVICES_DELETECHATSERVICE_H_
#define MAIN_SERVICES_DELETECHATSERVICE_H_

#include "../config.h"
#include "../user/chat/Chat.h"
#include "../user/User.h"
#include "../database/Database.h"
#include "ServiceInterface.h"

/**
 * Encargada de proveer el servicio de borrado de chats del servidor.
 * Un usuario que use este servicio borrará su chat con el usuario especificado.
 * El chat entre estos dos usuarios no se eliminará de la base de datos.
 */
class DeleteChatService: public ServiceInterface {
	friend class DeleteChatServiceTest;
public:
	virtual std::string getUri() const;
	virtual std::string executeRequest(const Json::Value &paramMap) const;

private:

	/**
	 * Metodo encargado de aplicar el servicio de borrado de chats del servidor.
	 * @param data informacion de entrada para este servicio.
	 * @return información sobre el resultado de aplicar este servicio.
	 */
	static Json::Value doDeleteChat(const Json::Value &data);
};

/**
 * Creador del servicio de borrado de chats del servidor.
 */
class DeleteChatServiceCreator: public ServiceCreatorInterface {

	virtual ServiceInterface* create();
};

#endif /* CURRENTCHATSSERVICE_H_ */
