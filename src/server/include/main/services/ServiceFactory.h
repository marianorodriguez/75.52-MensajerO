#ifndef SERVICE_FACTORY_H
#define SERVICE_FACTORY_H

#include <map>
#include <string>
#include <vector>

// Forwards
class Database;
class ServiceInterface;
class ServiceCreatorInterface;

/**
 * Clase encargada de devolver la instancia del servicio solicitado.
 */
class ServiceFactory{
public:
	/**
	 * Constructor
	 */
	ServiceFactory(Database& userDb, Database& chatDb);
	/**
	 * Destructor
	 */
	~ServiceFactory();

	/**
	 * Devuelve un servicio según su nombre
	 */
	ServiceInterface* createService(const std::string& serviceName) const;

	/**
	 * Agrega un creator, cuya clave es la que corresponde a la
	 * URI del servicio que genera.
	 */
	void addNewServiceCreator(ServiceCreatorInterface* creator);

private:
	std::map<std::string, ServiceCreatorInterface*> serviceMap;
	Database& userDb;
	Database& chatDb;
};

#endif // SERVICE_FACTORY_H
