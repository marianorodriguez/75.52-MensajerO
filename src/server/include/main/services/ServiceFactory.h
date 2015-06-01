#ifndef SERVICE_FACTORY_H
#define SERVICE_FACTORY_H

#include <map>
#include <string>
#include <vector>

// Forwards
class ServiceInterface;
class ServiceCreatorInterface;

class ServiceFactory{
public:
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
	 * Devuelve una lista de nombres de todos los servicios disponibles.
	 */
	std::vector<std::string> getServiceNameList() const;
	/**
	 * Agrega un creator, cuya clave es la que corresponde a la
	 * URI del servicio que genera.
	 */
	void addNewServiceCreator(ServiceCreatorInterface* creator);
private:
	std::map<std::string, ServiceCreatorInterface*> serviceMap;
};

#endif // SERVICE_FACTORY_H
