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

