#ifndef SERVICE_FACTORY_H
#define SERVICE_FACTORY_H

#include <map>
#include <string>
#include <vector>

// Forwards
class ServiceInterface;

class ServiceFactory{
public:
	enum ServiceInterfaceId {
		SIGNUP_SERVICE,
		//TODO: remover
		ECHO_SERVICE,
		NULL_SERVICE
	};
	/**
	 * Constructor
	 */
	ServiceFactory();
	/**
	 * Destructor
	 */
	~ServiceFactory();
	/**
	 * Devuelve un servicio según su nombre
	 */
	ServiceInterface* createService(const std::string& serviceName) const;
	/**
	 * Devuelve un servicio según su Id
	 */
	ServiceInterface* createServiceById(ServiceInterfaceId id) const;
	/**
	 * Devuelve una lista de nombres de todos los servicios disponibles.
	 */
	std::vector<std::string> getServiceNameList() const;
private:
	std::map<std::string, ServiceInterfaceId> serviceMap;
};

#endif // SERVICE_FACTORY_H
