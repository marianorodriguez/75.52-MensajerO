#ifndef REST_SERVER_H
#define REST_SERVER_H

#include "Connection.h"
#include "ServiceFactory.h"
#include "ConnectionManager.h"
#include "../ServerOptions.h"

// Forwards
struct mg_server;
struct mg_connection;

class ServiceCreatorInterface;

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
	 * Arranca al servidor
	 */
    void startServer();
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
	void handleConnection(struct mg_connection *connection) const;
	/**
	 * Agrega un servicio nuevo
	 */
	void addService(ServiceCreatorInterface* serviceCreator);
	/**
	 * Variables de configuración del servidor
	 */
    void setOptions (const ServerOptions& options);
private:
	/**
	 * Demora entre polls al servidor
	 */
    int pollDelay;
	/**
	 * Puerto de escucha
	 */
	int port;
	/**
	 * Número máximo de conexiones en simultaneo
	 */
	int maxConnections;
	/**
	 * Servidor principal
	 */
	struct mg_server* mainServer;
	/**
	 * Listeners paralelos al servidor
	 */
	std::vector<struct mg_server*> serverListeners;
	/**
	 * Servicios disponibles para ejecutar
	 */
	ServiceFactory serviceFactory;
	ConnectionManager* connectionManager;
	/**
	 * Inicial hilos de listeners
	 */
	void startSecondaryListeners();
};

#endif // REST_SERVER_H
