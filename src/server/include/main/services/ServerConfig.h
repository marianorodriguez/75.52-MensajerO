#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H
#include "RestServer.h"
#include "../ServerOptions.h"

/**
 * Encargada de configurar al servidor.
 */
class ServerConfig{
public:
	ServerConfig(const ServerOptions& options);
	/**
	 * Configura el servidor.
	 */
	void configure(RestServer& server) const;

protected:

	/**
	 * registra una serie de servicios al @param server.
	 */
	void addServiceCreators(RestServer& server) const ;
	ServerOptions options;
};

#endif // SERVERCONFIG_H
