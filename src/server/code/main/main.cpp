#include "../../include/main/services/ServerThread.h"
#include "../../include/main/services/ServerConfig.h"
#include "../../include/main/exceptions/BaseException.h"
#include "../../include/main/ServerOptions.h"
#include <iostream>

using namespace std;

int main(int argc, const char** argv) {

	string starting = "Starting server...";
	string shutting = "Shutting down server...";

	std::string text;
	bool exit = false;
	LoggerManager manager;
	ServerThread server;
	OptionMap optionMap = ArgsParser::parseArgs(argc, argv);
	ServerOptions options(optionMap);
	std::cout << "Reading config from: " << options.getConfigPath()
			<< std::endl;
	std::cout << "Using port: " << options.getServerPort() << std::endl;
	std::cout << "Using Database path: " << options.getDatabasePath()
			<< std::endl;
	std::cout << "Using client timeout: " << options.getUserAliveTime()
			<< std::endl;
	std::cout << "Using server's poll delay: " << options.getPollDelay()
			<< std::endl;
	ServerConfig config(options);
	server.addConfig(config);
	try {
		server.run();
		cout << starting << endl;
		Logger::getLogger()->write(Logger::INFO, starting);
		cout << "To finish, type 'exit'." << endl;
		while (!exit) {
			std::cin >> text;
			exit = (text.compare("exit") == 0);
		}
		server.shutdown();
	} catch (BaseException &e) {
		cout << e.getDescription() << endl;
	}
	std::cout << shutting << std::endl;
	Logger::getLogger()->write(Logger::INFO, shutting);
	Logger::getLogger()->saveStatus();
	server.join();
	return 0;
}
