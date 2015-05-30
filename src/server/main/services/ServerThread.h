#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include "../utilities/Thread.h"
#include "RestServer.h"

class ServerConfig;

class ServerThread : public Thread{
public:
	/**
	 * Constructor
	 */
	ServerThread();
	/**
	 * Termina el ciclo de polling y libera recursos
	 */
	void shutdown();
	/**
	 * Agrega un servicio nuevo
	 */
	void addService(ServiceCreatorInterface* serviceCreator);
    void addConfig(const ServerConfig& config);
protected:
	virtual void runFunction();
private:
	RestServer server;
	bool exit;
};

#endif // SERVER_THREAD_H
