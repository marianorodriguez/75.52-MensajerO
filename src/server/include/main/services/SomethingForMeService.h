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
	friend class SomethingForMeServiceTest;
public:
	virtual std::string getUri() const;
	virtual std::string executeRequest(const Json::Value &paramMap) const;

private:
	/**
	 * Aplica el servicio de actualizacion de mensajes.
	 * @param data informacion de entrada del servicio.
	 * @return listado de mensajes nuevos edl usuario.
	 */
	static Json::Value doSomethingForMe(const Json::Value &data);
};

/**
 * creador del servicio de actualizacion de mensajes.
 */
class SomethingForMeServiceCreator: public ServiceCreatorInterface {
	virtual ServiceInterface* create();
};

#endif /* SOMETHINGFORMESERVICE_H_ */
