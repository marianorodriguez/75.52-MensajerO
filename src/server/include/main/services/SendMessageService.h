#ifndef SENDMESSAGESERVICE_H_
#define SENDMESSAGESERVICE_H_

#include "ServiceInterface.h"
#include "../database/Database.h"
#include "../user/chat/Chat.h"
#include "../user/User.h"

/**
 * Clase encargada de proveer el servicio de envio de mensajes del servidor.
 * El usuario que use este servicio le enviará un mensaje a otro usuario especificado.
 */
class SendMessageService: public ServiceInterface {
	friend class SendMessageServiceTest;
	friend class BroadcastService;

public:
	SendMessageService(Database& userDb, Database& chatDb);
    virtual ~SendMessageService();
	virtual std::string getUri() const;
	virtual std::string executeRequest(const Json::Value &paramMap) const;
	/**
	 * Encargado de aplicar el servicio de envio de mensajes.
	 * @param data informacion de entrada.
	 * @return informacion sobre el resultado de la ejecucion de este servicio.
	 */
	Json::Value doSendMessage(const Json::Value &data) const;

private:
	static const std::string serviceName;
    Database& userDb;
	Database& chatDb;
};

/**
 * creador del servicio de envio de mensajes.
 */
class SendMessageServiceCreator : public ServiceCreatorInterface{
public:
    virtual ServiceInterface* create(Database& userDb, Database& chatDb);
};

#endif /* SENDMESSAGESERVICE_H_ */
