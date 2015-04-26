#include <cstdio>
#include <cstring>
#include<iostream>

#include "mongoose.h"
#include "json.h"
#include "utilities/Base64.h"

#include "RestServer.h"
#include "ServiceFactory.h"
#include "ServiceInterface.h"

/**
* Captura los requests que le llegan al servidor
*/
static int eventHandler(struct mg_connection *mgConnection, enum mg_event event) {
	RestServer* server = static_cast<RestServer*>(mgConnection->server_param);
	switch (event) {
		case MG_AUTH:
			return MG_TRUE;
		case MG_REQUEST:
			server->handleConnection(mgConnection);
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
	mg_set_option(this->server, "listening_port", "8081");
}

/**
 * Destructor
 */
RestServer::~RestServer(){
	shutdownServer();
}

void RestServer::addService (ServiceCreatorInterface* serviceCreator ){
	this->serviceFactory.addNewServiceCreator(serviceCreator);
}

void RestServer::pollServer(){
	mg_poll_server(this->server, 1000);
}

void RestServer::handleConnection(struct mg_connection *mgConnection) const{
	ServiceInterface* service;
	Connection connectionWrap(mgConnection);
	// Le saco la barra inicial
	std::string serviceName(connectionWrap.getUri().substr(1));
	service = this->serviceFactory.createService(serviceName);
	service->executeRequest(connectionWrap);
	delete service;
}

/**
 * Apago el servidor
 */
void RestServer::shutdownServer(){
	mg_destroy_server(&this->server);
}
