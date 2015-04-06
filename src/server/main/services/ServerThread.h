#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include "../utilities/Thread.h"
#include "RestServer.h"

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
protected:
	virtual void runFunction();
private:
	RestServer server;
	bool exit;
};

#endif // SERVER_THREAD_H
