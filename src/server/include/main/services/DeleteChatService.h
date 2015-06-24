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
public:
	DeleteChatService(Database& userDb, Database& chatDb);
	virtual ~DeleteChatService();
	virtual std::string getUri() const;
	virtual std::string executeRequest(const std::string &paramMap) const;
	/**
	 * Metodo encargado de aplicar el servicio de borrado de chats del servidor.
	 * @param data informacion de entrada para este servicio.
	 * @return información sobre el resultado de aplicar este servicio.
	 */
	std::string doDeleteChat(const std::string &data) const;

private:
	static const std::string serviceName;
	/** Base de datos de usuarios **/
	Database& userDb;
	/** Base de datos de chats **/
	Database& chatDb;
};

/**
 * Creador del servicio de borrado de chats del servidor.
 */
class DeleteChatServiceCreator: public ServiceCreatorInterface {

	virtual ServiceInterface* create(Database& userDb, Database& chatDb);
};

#endif /* CURRENTCHATSSERVICE_H_ */
