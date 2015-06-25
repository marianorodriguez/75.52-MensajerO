#ifndef ECHOSERVICE_H
#define ECHOSERVICE_H

#include "../../main/services/ServiceInterface.h"

class EchoService : public ServiceInterface{
public:
	/**
	 * Devuelve el nombre con el que se accederá al servicio
	 */
	std::string getUri() const;
	/**
	 * Responde al cliente con los mismos parámetros con los que fue llamado.
	 * @param connection contiene los datos de la conexion con el cliente.
	 */
	std::string executeRequest(const std::string &paramMap) const;
private:
	static const std::string serviceName;
};

class EchoServiceCreator : public ServiceCreatorInterface{
public:
    virtual ServiceInterface* create(Database& userDb, Database& chatDb);
};

#endif // ECHOSERVICE_H
