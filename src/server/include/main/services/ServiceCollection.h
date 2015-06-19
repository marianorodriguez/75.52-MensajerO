#ifndef SERVICECOLLECTION_H
#define SERVICECOLLECTION_H

#include <map>
#include <string>
#include <vector>

#include "ServiceInterface.h"
// Forwards
class ServiceInterface;

/**
 * Encargado de contener todos los servicios que proveerá el servidor.
 */
class ServiceCollection{
public:
	/**
	 * Destructor
	 */
	~ServiceCollection();

	/**
	 * Agrega un @param servicio a la colleción.
	 * @warning: la colección se encarga de eliminarlo del heap
	 */
	void addService(ServiceInterface* const service);

	/**
	 * Devuelve un servicio según su @param nombre
	 */
	ServiceInterface* getService(const std::string& nombre) const;

	/**
	 * Devuelve una lista de nombres de todos los servicios disponibles.
	 */
	std::vector<std::string> getServiceNameList() const;
private:

	/**
	 * mapa de servicios.
	 * dado un string con el nombre del servicio, devuelve la referencia al mismo.
	 */
	std::map<std::string, ServiceInterface*> serviceMap;
};

#endif // SERVICECOLLECTION_H
