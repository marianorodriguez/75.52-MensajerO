#include "../../include/main/utilities/Logger.h"
#include "json.h"

Logger* Logger::logInstance = NULL;
Mutex Logger::constructorMutex;
string Logger::logDir = "";

Logger::Logger(const std::string& config_dir) {

	Json::Value json_root;
	Json::Reader json_reader;
	Json::Value json_logger;

	std::ifstream json_file(config_dir);

	if (!json_file.good()) {
		string description = "Can't find the file " + config_dir + ".";
		BaseException e(description);
		throw e;
	}
	bool parsingSuccessful = json_reader.parse(json_file, json_root, false);
	json_file.close();

	if (parsingSuccessful) {
		json_logger = json_root["logger"];
		logDir = json_logger.get("logDir", DEFAULT_LOGGING_FILE).asString();
		this->file.open(this->logDir.c_str(), ofstream::trunc);
		setLoggingLevels(json_logger);
	}

}

void Logger::write(loggingLevel level, string text) {
	Lock(this->mutex);
	if (this->file.is_open()) {
		if (this->levels[level]) {
			string toWrite = Date::getDate() + " | " + Time::getTime() + " | "
					+ this->getWriteLevel(level) + ": " + text + "\n";
			this->file.write(toWrite.c_str(), strlen(toWrite.c_str()));
		}
	}
}

void Logger::saveStatus() {
	this->file.flush();
}

string Logger::getWriteLevel(const loggingLevel& level) {

	string ret;

	switch (level) {
	case ERROR:
		ret = "ERROR";
		break;
	case WARN:
		ret = "WARNING";
		break;
	case INFO:
		ret = "INFO";
		break;
	case DEBUG:
		ret = "DEBUG";
		break;
	default:
		ret = "?";
		break;
	}

	return ret;
}

void Logger::setLoggingLevels(const Json::Value& jsonLogger) {
	this->levels[ERROR] = jsonLogger["ERROR"].asBool();
	this->levels[WARN] = jsonLogger["WARNING"].asBool();
	this->levels[DEBUG] = jsonLogger["DEBUG"].asBool();
	this->levels[INFO] = jsonLogger["INFO"].asBool();
}

string Logger::getLogDir() {
	return logDir;
}

Logger::~Logger() {
	if (this->file.is_open()) {
		this->file.close();
	}
	this->logInstance = NULL;
}

Logger* Logger::getLogger() {
	if (!logInstance){
		Lock lock(constructorMutex);
		if (!logInstance){ // Sigue siendo poco thread-safe, pero muy poco
			logInstance = new Logger(JSON_CONFIG_FILE);
		}
	}
	return logInstance;
}

void Logger::destroy(){
	Lock lock(constructorMutex);
	delete logInstance;
	logInstance = 0;
}
