#include "ServerThread.h"

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

