#ifndef CURRENTCHATSSERVICE_H_
#define CURRENTCHATSSERVICE_H_
#include "ServiceInterface.h"
#include "user/User.h"
#include "database/Database.h"
#include "user/chat/Chat.h"

class CurrentChatsService: public ServiceInterface  {
	friend class CurrentChatsServiceTest;
public:
	/*
	* Devuelve el nombre del servicio: CurrentChats
	*/
	virtual std::string getUri() const;
	/**
	 * Devuelve chats activos
	 */
	virtual void executeRequest(const Connection& connection) const;
private:
	static const std::string serviceName;

	static Json::Value doCurrentChats(const Json::Value &data);
};

class CurrentChatsServiceCreator: public ServiceCreatorInterface{

	virtual ServiceInterface* create();
};

#endif /* CURRENTCHATSSERVICE_H_ */
