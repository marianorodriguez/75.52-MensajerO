#include "Logger.h"

Logger* Logger::logInstance = NULL;
string Logger::logDir = "";
mutex mtx;

Logger::Logger(string config_dir) {

	Json::Value json_root;
	Json::Reader json_reader;

	std::ifstream json_file(config_dir);

	if (!json_file.good()) {
		string configDir(config_dir);
		string description = "Can't find the file " + configDir + ".";
		FileNotFoundException * e = new FileNotFoundException(description);
		throw *e;
	}
	bool parsingSuccessful = json_reader.parse(json_file, json_root, false);
	json_file.close();

	if (parsingSuccessful) {
		this->json_logger = json_root["logger"];
		logDir = json_logger.get("logDir", DEFAULT_LOGGING_FILE).asString();
		this->file.open(this->logDir.c_str(), ofstream::trunc);
		setLoggingLevels();
	}

}

void Logger::write(loggingLevel level, string text) {

	if (this->file.is_open()) {
		if (this->levels[level]) {

			unique_lock<mutex> lock(mtx);

			string toWrite = Date::getDate() + " | " + Time::getTime() + " | "
					+ this->getWriteLevel(level) + ": " + text + "\n";
			this->file.write(toWrite.c_str(), strlen(toWrite.c_str()));
		}
	}
}

void Logger::saveStatus() {

	unique_lock<mutex> lock(mtx);
	this->file.flush();
}

string Logger::getWriteLevel(loggingLevel level) {

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

void Logger::setLoggingLevels() {

	Json::Value loggingLevels = this->json_logger.get("loggingLevels", "");
	this->levels[ERROR] = loggingLevels[ERROR].get("ERROR", false).asBool();
	this->levels[WARN] = loggingLevels[WARN].get("WARNING", false).asBool();
	this->levels[DEBUG] = loggingLevels[DEBUG].get("DEBUG", false).asBool();
	this->levels[INFO] = loggingLevels[INFO].get("INFO", false).asBool();
}

string Logger::getLogDir() {
	return logDir;
}

Logger::~Logger() {

	unique_lock<mutex> lock(mtx);

	if (this->file.is_open()) {
		this->file.close();
	}

	this->logInstance = NULL;
}

Logger* Logger::getLogger() {

	unique_lock<mutex> lock(mtx);

	if (logInstance == NULL)
		logInstance = new Logger(JSON_CONFIG_FILE);

	return logInstance;
}
