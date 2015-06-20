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
	friend class CurrentChatsServiceTest;
public:
	virtual std::string getUri() const;
	virtual std::string executeRequest(const Json::Value &paramMap) const;

private:

	/**
	 * Encargado de aplicar el servicio de consulta de chats.
	 * @param data informacion de entrada para este servicio.
	 * @return listado de chats activos del usuario que invocó este servicio.
	 */
	static Json::Value doCurrentChats(const Json::Value &data);
};

/**
 * Creador del servicio de consulta de chats.
 */
class CurrentChatsServiceCreator: public ServiceCreatorInterface{

	virtual ServiceInterface* create();
};

#endif /* CURRENTCHATSSERVICE_H_ */
