#ifndef REST_SERVER_H
#define REST_SERVER_H

#include "Connection.h"

// Forwards
struct mg_server;
struct mg_connection;

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
	int shutdownServer();
	/**
	 * Atrapa los requests
	 */
	void handleConnection(const Connection& connection) const;
private:
	struct mg_server *server;
};

#endif // REST_SERVER_H