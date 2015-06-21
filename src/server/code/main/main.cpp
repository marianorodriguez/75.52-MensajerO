#include "../../include/main/services/ServerThread.h"
#include "../../include/main/services/ServerConfig.h"
#include "../../include/main/exceptions/BaseException.h"
#include "../../include/main/ServerOptions.h"
#include <iostream>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

std::string getLocalIPAdress();

int main(int argc, const char** argv) {

	string IP = getLocalIPAdress();
	string starting = "Starting server...";
	string shutting = "Shutting down server...";

	if (IP != "unknown") {
		std::string text;
		bool exit = false;
		ServerThread server;
		OptionMap optionMap = ArgsParser::parseArgs(argc, argv);
		ServerOptions options(optionMap);
		std::cout << "Reading config from: " << options.getConfigPath()
				<< std::endl;
		std::cout << "Using port: " << options.getServerPort() << std::endl;
		std::cout << "Using IP address: " << IP << std::endl;
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
	}else{
		cout<< "Couldn't resolve the IP Address. Make sure you are connected in a network."<<endl;
	}
	return 0;
}

std::string getLocalIPAdress() {
	string IP = "unknown";
	struct ifaddrs *ifaddr, *ifa;
	int s;
	char host[NI_MAXHOST];

	if (getifaddrs(&ifaddr) == -1) {
		perror("getifaddrs");
		exit(EXIT_FAILURE);
	}

	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL)
			continue;

		s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host,
		NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

		if ((strcmp(ifa->ifa_name, "wlan0") == 0)
				&& (ifa->ifa_addr->sa_family == AF_INET)) {
			if (s != 0) {
				printf("getnameinfo() failed: %s\n", gai_strerror(s));
				exit(EXIT_FAILURE);
			}
			IP = host;
		}
	}

	freeifaddrs(ifaddr);
	return IP;
}
