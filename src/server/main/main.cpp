#include "services/ServerThread.h"
#include "exceptions/BaseException.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
	std::string text;
	bool exit = false;
	ServerThread server;
	try{
		server.run();
		cout<< "Levantando server..."<<endl<<"Para terminar, escriba 'salir'.";
		while (!exit){
			std::cin >> text;
			exit = (text.compare("salir") == 0);
		}
		server.shutdown();
	}catch(BaseException &e){

		cout<<e.what()<<endl;
	}
	std::cout << "Apagando..." << std::endl;
	server.join();
}

