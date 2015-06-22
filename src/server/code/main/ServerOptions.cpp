#include <getopt.h>
#include <iostream>
#include <fstream>
#include <map>
#include "json.h"
#include "../../include/main/ServerOptions.h"
#include "../../include/main/utilities/NumberConverter.h"
#include "../../include/main/utilities/Logger.h"

const std::string ServerOptions::kJsonServerRoot("server");
const std::string ServerOptions::kDefaultConfigPath("config/config.json");
// Valores default de onfigurables
const std::string ServerOptions::kDefaultDatabasePath("database");
const int ServerOptions::kDefaultPollDelay = 1000;
const int ServerOptions::kDefaultServerPort = 8081;
const int ServerOptions::kDefaultUserAliveTime = 5000;

ServerOptions::ServerOptions() {
	loadDefaultValues();
	OptionMap fileOptions = loadValuesFromFile();
}

ServerOptions::ServerOptions(const OptionMap& consoleOptions) {
	loadDefaultValues();
	OptionMap::const_iterator it = consoleOptions.find(ArgsParser::kConfigKey);
	if (it != consoleOptions.end()) {
		this->configPath = it->second;
	}
	OptionMap optionMap(consoleOptions);
	OptionMap fileOptions = loadValuesFromFile();
	// Priorizo los valores de la consola a los del json
	optionMap.insert(fileOptions.begin(), fileOptions.end());
	loadOptions(optionMap);
}

void ServerOptions::loadOptions(const OptionMap& optionMap) {
	OptionMap::const_iterator it = optionMap.find(ArgsParser::kDatabaseKey);
	if (it != optionMap.end()) {
		this->databasePath = it->second;
	}
	it = optionMap.find(ArgsParser::kServerPortKey);
	if (it != optionMap.end()) {
		this->serverPort = NumberConverter::getNumber(it->second);
	}
	it = optionMap.find(ArgsParser::kPollDelayKey);
	if (it != optionMap.end()) {
		this->pollDelay = NumberConverter::getNumber(it->second);
	}
	it = optionMap.find(ArgsParser::kAliveTimeKey);
	if (it != optionMap.end()) {
		this->userAliveTime = NumberConverter::getNumber(it->second);
	}
}

void ServerOptions::loadDefaultValues() {
	this->configPath = kDefaultConfigPath;
	this->databasePath = kDefaultDatabasePath;
	this->pollDelay = kDefaultPollDelay;
	this->serverPort = kDefaultServerPort;
	this->userAliveTime = kDefaultUserAliveTime;
}

OptionMap ServerOptions::loadValuesFromFile() {
	// Intento levantar con la ruta completa
	std::ifstream configFile(this->configPath);
	if (!configFile.is_open()) {
		Logger::getLogger()->write(Logger::WARN, "config.json missing");
		OptionMap map;
		return map;
	}
	return parseJson(configFile);
}

OptionMap ServerOptions::parseJson(std::ifstream& configFile) {
	OptionMap options;
	Json::Reader jsonReader;
	Json::Value jsonRoot, serverNode;
	bool parsingSuccessful = jsonReader.parse(configFile, jsonRoot, false);
	configFile.close();
	if (parsingSuccessful) {
		// TODO integrar configuracion del logger
		serverNode = jsonRoot[kJsonServerRoot];
		options[ArgsParser::kAliveTimeKey] = serverNode.get(
				ArgsParser::kAliveTimeKey, kDefaultUserAliveTime).asString();
		options[ArgsParser::kDatabaseKey] = serverNode.get(
				ArgsParser::kDatabaseKey, kDefaultDatabasePath).asString();
		options[ArgsParser::kPollDelayKey] = serverNode.get(
				ArgsParser::kPollDelayKey, kDefaultPollDelay).asString();
		options[ArgsParser::kServerPortKey] = serverNode.get(
				ArgsParser::kServerPortKey, kDefaultServerPort).asString();
	} else {
		Logger::getLogger()->write(Logger::WARN, "Invalid config.json");
	}
	return options;
}

std::string ServerOptions::getConfigPath() const {
	return this->configPath;
}

std::string ServerOptions::getDatabasePath() const {
	return this->databasePath;
}

int ServerOptions::getPollDelay() const {
	return this->pollDelay;
}

int ServerOptions::getServerPort() const {
	return this->serverPort;
}

int ServerOptions::getUserAliveTime() const {
	return this->userAliveTime;
}

const std::string ArgsParser::kAliveTimeKey("aliveTime");
const std::string ArgsParser::kConfigKey("config");
const std::string ArgsParser::kDatabaseKey("database");
const std::string ArgsParser::kPollDelayKey("pollDelay");
const std::string ArgsParser::kServerPortKey("port");

OptionMap ArgsParser::parseArgs(int argc, const char** argv) {
	OptionMap optionMap;
	char** optv = const_cast<char**>(argv);
	struct option longOptions[] = { { kAliveTimeKey.c_str(), required_argument,
			0, 'a' }, { kConfigKey.c_str(), required_argument, 0, 'c' }, {
			kDatabaseKey.c_str(), required_argument, 0, 'd' }, {
			kServerPortKey.c_str(), required_argument, 0, 'p' }, {
			kPollDelayKey.c_str(), required_argument, 0, 'P' }, { "help",
	no_argument, 0, 'h' }, { 0, 0, 0, 0 } };
	bool hasOptions = true;
	while (hasOptions) {
		char c = getopt_long(argc, optv, "a:c:d:p:P:h", longOptions, 0);
		if (c == -1) {
			hasOptions = false;
		}
		switch (c) {
		case 'a':
			optionMap[kAliveTimeKey] = optarg;
			break;
		case 'c':
			optionMap[kConfigKey] = optarg;
			break;
		case 'd':
			optionMap[kDatabaseKey] = optarg;
			break;
		case 'p':
			optionMap[kServerPortKey] = optarg;
			break;
		case 'P':
			optionMap[kPollDelayKey] = optarg;
			break;
		case 'h':
		default:
			printHelp();
			break;
		}
	}
	optind = 1;
	return optionMap;
}

void ArgsParser::printHelp() {
	std::cout << "=== MensajerO - Server ===" << std::endl;
	std::cout << "== Options == \n" << std::endl;
	std::cout << "-c --config <path>: config file path" << std::endl;
	std::cout << "-d --database <path>: database path" << std::endl;
	std::cout << "-p --port <port>: server's port number" << std::endl; //TODO hardcodear el puerto!! (desde el celu no varia / es al pedo que varie)
	std::cout
			<< "-P --pollDelay <msec>: delay between mongoose polling\
(mongoose)"
			<< std::endl;
	std::cout << "-a --aliveTime <msec>: client timeout." << std::endl;
}
