#include "../../include/main/services/ServerThread.h"
#include "../../include/main/services/ServerConfig.h"
#include "../../include/main/exceptions/BaseException.h"
#include "../../include/main/ServerOptions.h"
#include <iostream>

using namespace std;

int main(int argc, const char** argv) {

	std::string text;
	bool exit = false;
	ServerThread server;
	OptionMap optionMap = ArgsParser::parseArgs(argc, argv);
	ServerOptions options(optionMap);
	std::cout << "Leyendo config desde: " << options.getConfigPath() << std::endl;
	std::cout << "Utilizando puerto: " << options.getServerPort() << std::endl;
	std::cout << "Utilizando path de BD: " << options.getDatabasePath() << std::endl;
	std::cout << "Utilizando tiempo de vida de cliente: "
				<< options.getUserAliveTime() << std::endl;
	std::cout << "Utilizando tiempo entre escuchas: " << options.getPollDelay() << std::endl;
	ServerConfig config(options);
	server.addConfig(config);
	try{
		server.run();
		cout<< "Levantando server..."<<endl;
		cout<< "Para terminar, escriba 'salir'."<<endl;
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
