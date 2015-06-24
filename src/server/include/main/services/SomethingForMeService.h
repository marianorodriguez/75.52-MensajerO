#ifndef SOMETHINGFORMESERVICE_H_
#define SOMETHINGFORMESERVICE_H_
#include "ServiceInterface.h"
#include "../user/User.h"
#include "../user/chat/Chat.h"
#include "../database/Database.h"

/**
 * Clase encargada de realizar el servicio de actualizacion de mensajes del servidor.
 * El usuario que use este servicio recibirá un listado con los nuevos mensajes que le hayan enviado.
 */
class SomethingForMeService: public ServiceInterface {
public:

	SomethingForMeService(Database& userDb, Database& chatDb);
	virtual std::string getUri() const;
	virtual std::string executeRequest(const std::string &paramMap) const;
	/**
	 * Aplica el servicio de actualizacion de mensajes.
	 * @param data informacion de entrada del servicio.
	 * @return listado de mensajes nuevos edl usuario.
	 */
	std::string doSomethingForMe(const std::string &data) const;

private:
	static const std::string serviceName;
	Database& userDb;
	Database& chatDb;
};

/**
 * Creador del servicio de actualizacion de mensajes.
 */
class SomethingForMeServiceCreator: public ServiceCreatorInterface{
	virtual ServiceInterface* create(Database& userDb, Database& chatDb);
};

#endif /* SOMETHINGFORMESERVICE_H_ */
