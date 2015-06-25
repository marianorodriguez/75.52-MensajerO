#ifndef CURRENTCHATSSERVICE_H_
#define CURRENTCHATSSERVICE_H_
#include "ServiceInterface.h"
#include "../user/User.h"
#include "../database/Database.h"
#include "../user/chat/Chat.h"

/**
 * Clase encargada de realizar el servicio de consulta de chats de un usuario.
 * Un usuario que use este servicio recibirá un listado con todos sus chats activos hasta el momento.
 */
class CurrentChatsService: public ServiceInterface  {
public:
	CurrentChatsService(Database& userDb, Database& chatDb);
	virtual ~CurrentChatsService();
	/**
	* Devuelve el nombre del servicio: CurrentChats
	*/
	virtual std::string getUri() const;
	virtual std::string executeRequest(const std::string &paramMap) const;
	/**
	 * Encargado de aplicar el servicio de consulta de chats.
	 * @param data informacion de entrada para este servicio.
	 * @return listado de chats activos del usuario que invocó este servicio.
	 */
	std::string doCurrentChats(const std::string &data) const;

private:
	static const std::string serviceName;
	Json::Value serializeUserChats(const std::string& username,
								const std::vector<std::string>& chats) const;
	/**
	 * Base de datos de usuarios
	 */
	Database& userDb;
	/** Base de datos de chats **/
	Database& chatDb;
};

/**
 * Creador del servicio de consulta de chats.
 */
class CurrentChatsServiceCreator: public ServiceCreatorInterface{
	virtual ServiceInterface* create(Database& userDb, Database& chatDb);
};

#endif /* CURRENTCHATSSERVICE_H_ */
