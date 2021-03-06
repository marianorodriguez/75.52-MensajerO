#ifndef REST_SERVER_H
#define REST_SERVER_H

#include "Connection.h"
#include "ServiceFactory.h"
#include "../ServerOptions.h"
#include "../utilities/ConnectionManager.h"

// Forwards
struct mg_server;
struct mg_connection;
class ServiceCreatorInterface;
/**
 * Servidor que encapsula los servicios de REST.
 */
class RestServer {
	friend class RestServerTest;
	friend class ServerConfigTest;
public:

	RestServer();
	~RestServer();

	/**
	 * Arranca al servidor.
	 */
    void startServer();

	/**
	 * Desconecta el servidor.
	 */
	void shutdownServer();

	/**
	 * Verifica requests pendientes.
	 */
	void pollServer();

	/**
	 * Atrapa requests y los procesa.
	 * @param connection información sobre el request atrapado.
	 */
	void handleConnection(struct mg_connection *connection) const;

	/**
	 * Registra un nuevo servicio en el servidor.
	 * @param serviceCreator creador del servicio que se desea registrar.
	 */
	void addService(ServiceCreatorInterface* serviceCreator);

	/**
	 * Configura los parametros del servidor.
	 * @param options opciones de configuracion del servidor.
	 */
    void setOptions (const ServerOptions& options);
    static const std::string kInvalidRequestMsg;

private:

	/**
	 * Demora entre polls al servidor.
	 */
    int pollDelay;

	/**
	 * Puerto de escucha del servidor.
	 */
	int port;

	/**
	 * Servidor mongoose que se está encapsulando.
	 */
	struct mg_server *server;

	/**
	 * Directorio con las bases de datos de usuarios y chats
	 */
	std::string userDbPath, chatDbPath;
	/**
	 * Bases de datos utilizadas por los servicios
	 */
	Database userDb, chatDb;
	/**
	 * Fabrica de servicios disponibles para ejecutar.
	 */
	ServiceFactory serviceFactory;

	/**
	 * procesa la conexion/desconexion de los usuarios que ingresan al sistema.
	 */
	ConnectionManager* connectionManager;
	/**
	 * Nombre del directorio default de bases de datos
	 */
	static const std::string kPathSeparator;
	static const std::string kDefaultDBPath;
	static const std::string kDefaultUserFolder;
	static const std::string kDefaultChatFolder;
};

#endif // REST_SERVER_H
