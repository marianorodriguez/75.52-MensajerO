#include "ServerConfig.h"
#include "ServerThread.h"

ServerThread::ServerThread(){
}

void ServerThread::runFunction(){
	this->exit = false;
	while (!this->exit){
		this->server.pollServer();
	}
	this->server.shutdownServer();
}

void ServerThread::shutdown(){
	this->exit = true;
}

void ServerThread::addService(ServiceCreatorInterface* serviceCreator){
	this->server.addService(serviceCreator);
}

void ServerThread::addConfig(const ServerConfig& config){
	config.configure(this->server);
}
