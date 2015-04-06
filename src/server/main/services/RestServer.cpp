#include <cstdio>
#include <cstring>

#include "mongoose.h"

#include "RestServer.h"
#include "ServiceFactory.h"
#include "ServiceInterface.h"

/**
* Captura los requests que le llegan al servidor
*/
static int eventHandler(struct mg_connection *conn, enum mg_event event) {
	RestServer* server = static_cast<RestServer*>(conn->server_param);
	Connection connectionWrap(conn);
	switch (event) {
		case MG_AUTH:
			return MG_TRUE;
		case MG_REQUEST:
			server->handleConnection(connectionWrap);
			return MG_TRUE;
		default:
			return MG_FALSE;
	}
}

/**
 * Constructor
 */
RestServer::RestServer(){
	this->server = mg_create_server(this, eventHandler);
	//TODO: getter y setter o singleton
	this->serviceFactory = new ServiceFactory();
	mg_set_option(this->server, "listening_port", "8081");
}

/**
 * Destructor
 */
RestServer::~RestServer(){
	shutdownServer();
}

void RestServer::pollServer(){
	mg_poll_server(this->server, 1000);
}


void RestServer::handleConnection(const Connection& connection) const{
	ServiceInterface* service;
	// Le saco la barra inicial
	std::string serviceName(connection.getUri().substr(1));
	service = this->serviceFactory->createService(serviceName);
	service->executeRequest(connection);
}

/**
 * Apago el servidor
 */
void RestServer::shutdownServer(){
	mg_destroy_server(&this->server);
}
