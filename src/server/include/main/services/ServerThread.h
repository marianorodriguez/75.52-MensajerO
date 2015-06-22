#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include "../utilities/Thread.h"
#include "RestServer.h"

class ServerConfig;

/**
 * Hilo dedicado a correr una instancia del servidor
 */
class ServerThread : public Thread{
public:
	ServerThread();
	/**
	 * Termina el ciclo de polling y libera recursos.
	 */
	void shutdown();
	/**
	 * Agrega un servicio nuevo
	 */
	void addService(ServiceCreatorInterface* serviceCreator);
	/**
	 * Configura el servidor y bases de datos.
	 */
	void addConfig(const ServerConfig& config);
protected:
	virtual void runFunction();
private:
	/**
	 * Wrapper del servidor mongoose
	 */
	RestServer server;
	bool exit;
};

#endif // SERVER_THREAD_H
