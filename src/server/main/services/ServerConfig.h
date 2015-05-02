#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H
#include "services/RestServer.h"
#include <ServerOptions.h>

class ServerConfig{
public:
	ServerConfig(const ServerOptions& options);
	/**
	 * Configura el servidor
	 */
	void configure(RestServer& server);
protected:
	void addServiceCreators(RestServer& server);
};

#endif // SERVERCONFIG_H
