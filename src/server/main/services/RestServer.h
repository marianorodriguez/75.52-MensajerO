#ifndef REST_SERVER_H
#define REST_SERVER_H

#include "Connection.h"

// Forwards
struct mg_server;
struct mg_connection;

class ServiceFactory;

/**
 * Servidor de servicios rest
 */
class RestServer {
public:
	/**
	 * Constructor
	 */
	RestServer();
	/**
	 * Destructor
	 */
	~RestServer();
	/**
	 * Desconecta el servidor
	 */
	void shutdownServer();
	/**
	 * Verifica requests pendientes
	 */
	void pollServer();
	/**
	 * Atrapa los requests
	 */
	void handleConnection(const Connection& connection) const;
private:
	/**
	 * Server mongoose
	 */
	struct mg_server *server;
	/**
	 * Servicios disponibles para ejecutar
	 */
	ServiceFactory* serviceFactory;
};

#endif // REST_SERVER_H