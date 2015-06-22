#include "../../include/main/services/ServerThread.h"
#include "../../include/main/services/ServerConfig.h"
#include "../../include/main/exceptions/BaseException.h"
#include "../../include/main/ServerOptions.h"
#include <iostream>

int main(int argc, const char** argv) {

	std::string starting = "Starting server...";
	std::string running = "Running server...";
	std::string shutting = "Shutting down server...";
	try {
		Logger::getLogger()->write(Logger::INFO, starting);
	} catch (BaseException &e) {
		cout << e.getDescription() << endl;
		return -1;
	}
	std::string text;
	bool exit = false;
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
	ServerThread server;
	try {
		server.addConfig(config);
		server.run();
		cout <<starting << endl;
		Logger::getLogger()->write(Logger::INFO, running);
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
}
