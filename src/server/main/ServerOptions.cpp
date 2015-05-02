#include <getopt.h>
#include <iostream>
#include <fstream>
#include "json.h"
#include "ServerOptions.h"


const std::string ServerOptions::kJsonServerRoot("server");
const std::string ServerOptions::kDefaultConfigPath("config.json");
const std::string ServerOptions::kDefaultDatabasePath("database");
const int ServerOptions::kDefaultPollDelay = 1000;
const int ServerOptions::kDefaultServerPort = 8081;
const int ServerOptions::kDefaultUserAliveTime = 5000;

ServerOptions::ServerOptions(){
	loadDefaultValues();
	OptionMap fileOptions = loadValuesFromFile();
}

ServerOptions::ServerOptions(const OptionMap& optionMap){
	loadDefaultValues();
	OptionMap::const_iterator it = optionMap.find(ArgsParser::kConfigKey);
	if (it != optionMap.end()){
		this->configPath = it->second;
	}
	OptionMap fileOptions = loadValuesFromFile();
}

void ServerOptions::loadDefaultValues(){
	this->configPath = kDefaultConfigPath;
	this->databasePath = kDefaultDatabasePath;
	this->pollDelay = kDefaultPollDelay;
	this->serverPort = kDefaultServerPort;
	this->userAliveTime = kDefaultUserAliveTime;
}

OptionMap ServerOptions::loadValuesFromFile(){
	// Intento levantar con la ruta completa
	std::ifstream configFile(this->configPath);
	if (!configFile.is_open()){
		this->configPath.append(kDefaultConfigPath);
		configFile.open(this->configPath);
	}
	if (!configFile.is_open()){
		OptionMap map;
		return map;
	}
	return parseJson(configFile);
}

OptionMap ServerOptions::parseJson(std::ifstream& configFile){
	OptionMap options;
	Json::Reader jsonReader;
	Json::Value jsonRoot, serverNode;
	bool parsingSuccessful = jsonReader.parse(configFile, jsonRoot, false);
	configFile.close();

	if (parsingSuccessful) {
		// TODO integrar configuracion del logger
		serverNode = jsonRoot[kJsonServerRoot];
		/**logDir = json_logger.get("logDir", DEFAULT_LOGGING_FILE).asString();
		this->file.open(this->logDir.c_str(), ofstream::trunc);
		setLoggingLevels();**/
	}
	return options;
}

std::string ServerOptions::getConfigPath(){
	return this->configPath;
}


std::string ServerOptions::getDatabasePath(){
	return this->databasePath;
}

int ServerOptions::getPollDelay(){
	return this->pollDelay;
}

int ServerOptions::getServerPort(){
	return this->serverPort;
}

int ServerOptions::getUserAliveTime(){
	return this->userAliveTime;
}

const std::string ArgsParser::kAliveTimeKey("aliveTime");
const std::string ArgsParser::kConfigKey("config");
const std::string ArgsParser::kDatabaseKey("database");
const std::string ArgsParser::kPollDelayKey("pollDelay");
const std::string ArgsParser::kServerPortKey("port");

OptionMap ArgsParser::parseArgs(int argc, char** argv){
	OptionMap optionMap;
	struct option longOptions[] =
	{
		{kAliveTimeKey.c_str(), required_argument, 0, 'a'},
		{kConfigKey.c_str(), required_argument, 0, 'c'},
		{kDatabaseKey.c_str(), required_argument, 0, 'd'},
		{kServerPortKey.c_str(), required_argument, 0, 'p'},
		{kPollDelayKey.c_str(), required_argument, 0, 'P'},
		{"help", no_argument, 0, 'h'},
		{0, 0, 0, 0}
	};
	bool hasOptions = true;
	while (hasOptions){
		char c = getopt_long (argc, argv, "a:c:d:p:P:h", longOptions, 0);
		if (c == -1){
			hasOptions = false;
		}
		switch (c){
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

void ArgsParser::printHelp(){
	std::cout << "=== MensajerO - Servidor ===" << std::endl;
	std::cout << "== Opciones == \n" << std::endl;
	std::cout << "-c --config <path>: directorio del archivo de config" << std::endl;
	std::cout << "-d --database <path>: directorio de la base de datos" << std::endl;
	std::cout << "-p --port <port>: numero del puerto del servidor" << std::endl;
	std::cout << "-P --pollDelay <msec>: demora entre lecturas del socket\
(mongoose)" << std::endl;
	std::cout << "-a --aliveTime <msec>: tiempo que se considera que un \
usuario esta conectado" << std::endl;
}
