#include <cppunit/config/SourcePrefix.h>
#include <thread>
#include "LoggerTest.h"
#include "utilities/Logger.h"

CPPUNIT_TEST_SUITE_REGISTRATION(LoggerTest);

Logger* logger;

void writeAllLevels(Logger* log) {

	log->write(Logger::DEBUG, "This is a Debug log.");
	log->write(Logger::WARN, "This is a Warning log.");
	log->write(Logger::ERROR, "This is an Error log.");
	log->write(Logger::INFO, "This is an Info log.");
}

void write50Times() {

	logger = Logger::getLogger();

	for (int i = 0; i < 50; i++) {
		logger->write(Logger::INFO, "I'm testing thread support");
	}

	logger->saveStatus();
}

string getTextFromFile(string dir) {

	ifstream file(dir);

	file.seekg(0, file.end);
	int length = file.tellg();
	file.seekg(0, file.beg);
	std::string text;
	text.resize(length);
	file.read(&text.at(0), length);

	return text;
}

void LoggerTest::should_be_singleton() {

	Logger* logger1 = Logger::getLogger();
	Logger* logger2 = Logger::getLogger();
	Logger* logger3 = Logger::getLogger();

	CPPUNIT_ASSERT(logger1 == logger2);
	CPPUNIT_ASSERT(logger2 == logger3);
	CPPUNIT_ASSERT(logger1 == logger3);

	delete logger1;
}

void LoggerTest::should_instantiate_logger() {

	logger = Logger::getLogger();

	CPPUNIT_ASSERT(logger != NULL);

	delete logger;
}

void LoggerTest::should_return_log_path() {

	logger = Logger::getLogger();
	string logDir = "";

	Json::Value json_root;
	Json::Reader json_reader;
	std::ifstream json_file(JSON_CONFIG_FILE);
	bool parsingSuccessful = json_reader.parse(json_file, json_root, false);

	if (parsingSuccessful) {
		Json::Value loggerDir = json_root["logger"];
		logDir = loggerDir.get("logDir", DEFAULT_LOGGING_FILE).asString();
	}

	CPPUNIT_ASSERT(logDir == logger->getLogDir());

	delete logger;
}

void LoggerTest::should_return_loggingLevels() {

	logger = Logger::getLogger();
	CPPUNIT_ASSERT(logger->getWriteLevel(Logger::ERROR) == "ERROR");
	CPPUNIT_ASSERT(logger->getWriteLevel(Logger::WARN) == "WARNING");
	CPPUNIT_ASSERT(logger->getWriteLevel(Logger::INFO) == "INFO");
	CPPUNIT_ASSERT(logger->getWriteLevel(Logger::DEBUG) == "DEBUG");

	delete logger;
}

void LoggerTest::should_write_only_a_debug() {

	logger = Logger::getLogger();
	logger->levels[Logger::DEBUG] = true;
	logger->levels[Logger::WARN] = false;
	logger->levels[Logger::ERROR] = false;
	logger->levels[Logger::INFO] = false;

	writeAllLevels(logger);
	logger->saveStatus();

	string text = getTextFromFile(logger->getLogDir());

	size_t debugFound = text.find("This is a Debug log.");
	size_t warnFound = text.find("This is a Warning log.");
	size_t errorFound = text.find("This is an Error log.");
	size_t InfoFound = text.find("This is an Info log.");

	CPPUNIT_ASSERT(debugFound != string::npos);
	CPPUNIT_ASSERT(warnFound == string::npos);
	CPPUNIT_ASSERT(errorFound == string::npos);
	CPPUNIT_ASSERT(InfoFound == string::npos);

	delete logger;
}

void LoggerTest::should_write_only_an_error() {

	logger = Logger::getLogger();
	logger->levels[Logger::ERROR] = true;
	logger->levels[Logger::DEBUG] = false;
	logger->levels[Logger::WARN] = false;
	logger->levels[Logger::INFO] = false;

	writeAllLevels(logger);
	logger->saveStatus();

	string text = getTextFromFile(logger->getLogDir());

	size_t debugFound = text.find("This is a Debug log.");
	size_t warnFound = text.find("This is a Warning log.");
	size_t errorFound = text.find("This is an Error log.");
	size_t InfoFound = text.find("This is an Info log.");

	CPPUNIT_ASSERT(errorFound != string::npos);
	CPPUNIT_ASSERT(debugFound == string::npos);
	CPPUNIT_ASSERT(warnFound == string::npos);
	CPPUNIT_ASSERT(InfoFound == string::npos);

	delete logger;
}

void LoggerTest::should_write_only_a_warning() {

	logger = Logger::getLogger();
	logger->levels[Logger::WARN] = true;
	logger->levels[Logger::DEBUG] = false;
	logger->levels[Logger::ERROR] = false;
	logger->levels[Logger::INFO] = false;

	writeAllLevels(logger);
	logger->saveStatus();

	string text = getTextFromFile(logger->getLogDir());

	size_t debugFound = text.find("This is a Debug log.");
	size_t warnFound = text.find("This is a Warning log.");
	size_t errorFound = text.find("This is an Error log.");
	size_t InfoFound = text.find("This is an Info log.");

	CPPUNIT_ASSERT(warnFound != string::npos);
	CPPUNIT_ASSERT(debugFound == string::npos);
	CPPUNIT_ASSERT(errorFound == string::npos);
	CPPUNIT_ASSERT(InfoFound == string::npos);

	delete logger;
}

void LoggerTest::should_write_only_an_info() {

	logger = Logger::getLogger();
	logger->levels[Logger::INFO] = true;
	logger->levels[Logger::DEBUG] = false;
	logger->levels[Logger::WARN] = false;
	logger->levels[Logger::ERROR] = false;

	writeAllLevels(logger);
	logger->saveStatus();

	string text = getTextFromFile(logger->getLogDir());

	size_t debugFound = text.find("This is a Debug log.");
	size_t warnFound = text.find("This is a Warning log.");
	size_t errorFound = text.find("This is an Error log.");
	size_t InfoFound = text.find("This is an Info log.");

	CPPUNIT_ASSERT(InfoFound != string::npos);
	CPPUNIT_ASSERT(debugFound == string::npos);
	CPPUNIT_ASSERT(warnFound == string::npos);
	CPPUNIT_ASSERT(errorFound == string::npos);

	delete logger;
}

void LoggerTest::should_throw_file_not_found_exception() {

	CPPUNIT_ASSERT_THROW(new Logger("invalid route"), FileNotFoundException);
}
