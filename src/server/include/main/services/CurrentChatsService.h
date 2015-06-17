#ifndef CURRENTCHATSSERVICE_H_
#define CURRENTCHATSSERVICE_H_
#include "ServiceInterface.h"
#include "../user/User.h"
#include "../database/Database.h"
#include "../user/chat/Chat.h"

class CurrentChatsService: public ServiceInterface  {
public:
	CurrentChatsService(Database& userDb, Database& chatDb);
	virtual ~CurrentChatsService();
	/*
	* Devuelve el nombre del servicio: CurrentChats
	*/
	virtual std::string getUri() const;
	/**
	 * Devuelve chats activos
	 */
	virtual std::string executeRequest(const Json::Value &paramMap) const;
	Json::Value doCurrentChats(const Json::Value &data) const;
private:
	static const std::string serviceName;
	Json::Value serializeUserChats(const std::string& username,
								const std::vector<std::string>& chats) const;
	/** Base de datos de usuarios **/
	Database& userDb;
	/** Base de datos de chats **/
	Database& chatDb;
};

class CurrentChatsServiceCreator: public ServiceCreatorInterface{
	virtual ServiceInterface* create(Database& userDb, Database& chatDb);
};

#endif /* CURRENTCHATSSERVICE_H_ */
