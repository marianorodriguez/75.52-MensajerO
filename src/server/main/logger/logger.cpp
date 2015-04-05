#include "logger.h"

logger* logger::logInstance = NULL;
string logger::logDir = "";

logger::logger() {

	Json::Value json_root;
	Json::Reader json_reader;
	std::ifstream json_file(JSON_CONFIG_FILE);
	bool parsingSuccessful = json_reader.parse(json_file, json_root, false);

	if (parsingSuccessful) {
		this->json_logger = json_root["logger"];
		logDir = json_logger.get("logDir", DEFAULT_LOGGING_FILE).asString();
		this->file = new ofstream;
		this->file->open(this->logDir.c_str(), ofstream::trunc);
		setLoggingLevels();
		dateStamp();
	}
}

void logger::write(loggingLevel level, string text) {

	if (this->file->is_open()) {
		if (this->levels[level]) {
			this->file->write("\n", strlen("\n"));
			string toWrite = this->getWriteLevel(level) + ": " + text;
			this->file->write(toWrite.c_str(), strlen(toWrite.c_str()));
		}
	}
}

void logger::saveStatus() {
	this->file->close();
	this->file->open(logDir.c_str(), ofstream::app);
}

void logger::dateStamp() {
	time_t date;
	time(&date);
	string sDate = ctime(&date);
	string separator = "-------------------------------------------------";
	this->file->write(separator.c_str(), strlen(separator.c_str()));
	this->file->write("\n", strlen("\n"));
	sDate.append(separator);
	this->file->write(sDate.c_str(), strlen(sDate.c_str()));
	//this->file->write("\n", strlen("\n"));
}

string logger::getWriteLevel(loggingLevel level) {

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

void logger::setLoggingLevels() {

	Json::Value loggingLevels = this->json_logger.get("loggingLevels", "");
	this->levels[ERROR] = loggingLevels[ERROR].get("ERROR", false).asBool();
	this->levels[WARN] = loggingLevels[WARN].get("WARNING", false).asBool();
	this->levels[DEBUG] = loggingLevels[DEBUG].get("DEBUG", false).asBool();
	this->levels[INFO] = loggingLevels[INFO].get("INFO", false).asBool();
}

string logger::getLogDir() {
	return logDir;
}

logger::~logger() {
	this->file->close();
	delete this->file;
}

logger* logger::getLogger() {
	if (logInstance == NULL)
		logInstance = new logger();
	return logInstance;
}
