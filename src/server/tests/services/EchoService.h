#ifndef ECHOSERVICE_H
#define ECHOSERVICE_H

#include "services/ServiceInterface.h"

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
	void executeRequest(const Connection& connection) const;
private:
	static const std::string serviceName;
};

class EchoServiceCreator : public ServiceCreatorInterface{
public:
    virtual ServiceInterface* create();
};

#endif // ECHOSERVICE_H
