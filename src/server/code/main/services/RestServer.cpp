#include <cstring>
#include<iostream>

#include "mongoose.h"
#include "json.h"
#include "../../include/main/utilities/Base64.h"
#include "../../include/main/utilities/NumberConverter.h"

#include "../../include/main/services/RestServer.h"
#include "../../include/main/services/ServiceFactory.h"
#include "../../include/main/services/ServiceInterface.h"

/**
* Captura los requests que le llegan al servidor
*/
static int eventHandler(struct mg_connection *mgConnection, enum mg_event event) {
	RestServer* server = static_cast<RestServer*>(mgConnection->server_param);
	switch (event) {
		case MG_AUTH:
			return MG_TRUE;
		case MG_REQUEST:
			std::cout << "atendiendo request"<< std::endl;
			server->handleConnection(mgConnection);
			std::cout << "request terminado"<< std::endl;
			return MG_TRUE;
		default:
			return MG_FALSE;
	}
}

/**
 * Constructor
 */
RestServer::RestServer(){
	this->pollDelay = 1000;
	this->port = 8081;
	this->maxConnections = 20;
	startServer();
	connectionManager = ConnectionManager::getInstance();
	connectionManager->startUpdating();
}

/**
 * Destructor
 */
RestServer::~RestServer(){
	connectionManager->stopUpdating();
	ConnectionManager::destroyInstance();
	shutdownServer();
}

void RestServer::setOptions(const ServerOptions& options){
	shutdownServer();
	this->pollDelay = options.getPollDelay() * 10;
	this->port = options.getServerPort();
	options.getDatabasePath();
	startServer();
	
}


void RestServer::addService (ServiceCreatorInterface* serviceCreator ){
	this->serviceFactory.addNewServiceCreator(serviceCreator);
}

void RestServer::pollServer(){
	mg_poll_server(this->mainServer, this->pollDelay);
}

void RestServer::handleConnection(struct mg_connection *mgConnection) const{
	ServiceInterface* service;
	Connection connectionWrap(mgConnection);
	// Le saco la barra inicial
	std::string serviceName(connectionWrap.getUri().substr(1));
	service = this->serviceFactory.createService(serviceName);
	std::cout<<"executing "<<serviceName<<std::endl;
	std::string response = service->executeRequest(connectionWrap.getParamMap());
	connectionWrap.printMessage(response);
	delete service;
}

static void *serve(void *mgServer) {
	for (;;) mg_poll_server((struct mg_server *) mgServer, 10000);
	return NULL;
}

/**
 * Arranco el servidor
 */
void RestServer::startServer(){
	//shutdownServer();
	this->mainServer = mg_create_server(this, eventHandler);
	
	std::string strPort = NumberConverter::getString(port);
	mg_set_option(this->mainServer, "listening_port", strPort.c_str());

	startSecondaryListeners();
}

void RestServer::startSecondaryListeners(){
	this->serverListeners.resize(this->maxConnections);
	std::cout << "Iniciando " << this->maxConnections << " listeners" << std::endl;
	for (int i = 0; i < this->maxConnections; ++i){
		struct mg_server* listener = mg_create_server(this, eventHandler);
		std::string strPort = NumberConverter::getString(port);
		mg_set_option(listener, "listening_port", strPort.c_str());
		mg_start_thread(serve, listener);
		this->serverListeners[i] = listener;
	}
}


/**
 * Apago el servidor
 */
void RestServer::shutdownServer(){
	mg_destroy_server(&this->mainServer);
}
