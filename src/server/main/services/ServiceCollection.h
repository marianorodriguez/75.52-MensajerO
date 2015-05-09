#ifndef SERVICECOLLECTION_H
#define SERVICECOLLECTION_H

#include <map>
#include <string>
#include <vector>

#include "ServiceInterface.h"
// Forwards
class ServiceInterface;

class ServiceCollection{
public:
	/**
	 * Destructor
	 */
	~ServiceCollection();
	/**
	 * Agrega un servicio a la colleción.
	 * @warning: la colección se encarga de eliminarlo del heap
	 */
	void addService(ServiceInterface* const service);
	/**
	 * Devuelve un servicio según su nombre
	 */
	ServiceInterface* getService(const std::string& serviceName) const;
	/**
	 * Devuelve una lista de nombres de todos los servicios disponibles.
	 */
	std::vector<std::string> getServiceNameList() const;
private:
	std::map<std::string, ServiceInterface*> serviceMap;
};

#endif // SERVICECOLLECTION_H
