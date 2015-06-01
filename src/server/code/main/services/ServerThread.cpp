#include "../../../include/main/services/ServerConfig.h"
#include "../../../include/main/services/ServerThread.h"

ServerThread::ServerThread(){
	this->exit = false;
}

void ServerThread::runFunction(){
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
