#include "services/ServerThread.h"
#include "services/ServerConfig.h"
#include "exceptions/BaseException.h"
#include <iostream>

using namespace std;

int main() {
	std::string text;
	bool exit = false;
	ServerThread server;
	ServerConfig config;
	server.addConfig(config);
	try{
		server.run();
		cout<< "Levantando server..."<<endl<<"Para terminar, escriba 'salir'.";
		while (!exit){
			std::cin >> text;
			exit = (text.compare("salir") == 0);
		}
		server.shutdown();
	}catch(BaseException &e){
		cout<<e.getDescription()<<endl;
	}
	std::cout << "Apagando..." << std::endl;
	server.join();
}
