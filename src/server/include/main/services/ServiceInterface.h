#ifndef SERVICE_INTERFACE_H
#define SERVICE_INTERFACE_H

#include "Connection.h"
#include "ConnectionManager.h"
#include "json/json.h"

class ServiceInterface{
public:
	/**
	 * Destructor
	 */
	virtual ~ServiceInterface() {}
	/**
	 * Devuelve el nombre con el que se accederá al servicio
	 * ej: localhost:8080/foo es capturado por un servicio cuyo uri es "foo"
	 */
	virtual std::string getUri() const = 0;
	/**
	 * Ejecuta el servicio instanciado
	 * @param connection contiene los datos de la conexion con el cliente.
	 */
	virtual std::string executeRequest(const Json::Value &data) const = 0;
};

class ServiceCreatorInterface{
public:
	virtual ~ServiceCreatorInterface() {}
	/**
	 * Devuelve un puntero a una instancia de un servicio
	 */
	virtual ServiceInterface* create(Database& userDb, Database& chatDb) = 0;
};

#endif // SERVICE_INTERFACE_H
