#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H
#include <string>
#include "services/RestServer.h"

class ServerConfig{
public:
	//TODO Analizar que parámetros requiere para cargar configuraciones
	ServerConfig(const std::string& configPath = "");
	/**
	 * Configura el servidor
	 */
	void configure(RestServer& server);
protected:
	void addServiceCreators(RestServer& server);
private:	
	static const std::string kDefaultConfigPath;
};

#endif // SERVERCONFIG_H
