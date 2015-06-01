#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H
#include "RestServer.h"
#include "../ServerOptions.h"

class ServerConfig{
public:
	ServerConfig(const ServerOptions& options);
	/**
	 * Configura el servidor
	 */
	void configure(RestServer& server) const;
protected:
	void addServiceCreators(RestServer& server) const ;
	ServerOptions options;
};

#endif // SERVERCONFIG_H
