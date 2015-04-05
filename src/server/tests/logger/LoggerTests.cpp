#include <cppunit/config/SourcePrefix.h>
#include "loggerTests.h"
#include <stdio.h>
#include "../../main/logger/Logger.h"

CPPUNIT_TEST_SUITE_REGISTRATION(loggerTests);

Logger* logger;

void writeAllLevels(Logger* log) {

	log->write(Logger::DEBUG, "This is a Debug log.");
	log->write(Logger::WARN, "This is a Warning log.");
	log->write(Logger::ERROR, "This is an Error log.");
	log->write(Logger::INFO, "This is an Info log.");
}

void write50Times(string thread) {

	logger = Logger::getLogger();

	for (int i = 0; i < 50; i++) {
		logger->write(Logger::DEBUG,
				"I'm testing thread support on thread n" + thread);
	}

	logger->saveStatus();
}

string getTextFromFile(string dir) {

	ifstream file(dir);

	file.seekg(0, file.end);
	int length = file.tellg();
	file.seekg(0, file.beg);
	char* buffer = new char[length];
	file.read(buffer, length);

	string text(buffer);
	return text;
}

void loggerTests::should_be_singleton() {

	Logger* logger1 = Logger::getLogger();
	Logger* logger2 = Logger::getLogger();
	Logger* logger3 = Logger::getLogger();

	CPPUNIT_ASSERT(logger1 == logger2);
	CPPUNIT_ASSERT(logger2 == logger3);
	CPPUNIT_ASSERT(logger1 == logger3);
}

void loggerTests::should_instantiate_logger() {

	logger->logInstance = NULL;
	logger = Logger::getLogger();

	CPPUNIT_ASSERT(logger != NULL);
}

void loggerTests::should_return_log_path() {

	logger->logInstance = NULL;
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
}

void loggerTests::should_return_loggingLevels() {

	logger->logInstance = NULL;
	logger = Logger::getLogger();
	CPPUNIT_ASSERT(logger->getWriteLevel(Logger::ERROR) == "ERROR");
	CPPUNIT_ASSERT(logger->getWriteLevel(Logger::WARN) == "WARNING");
	CPPUNIT_ASSERT(logger->getWriteLevel(Logger::INFO) == "INFO");
	CPPUNIT_ASSERT(logger->getWriteLevel(Logger::DEBUG) == "DEBUG");

}

void loggerTests::should_write_only_a_debug() {

	logger->logInstance = NULL;
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
}

void loggerTests::should_write_only_an_error() {

	logger->logInstance = NULL;
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
}

void loggerTests::should_write_only_a_warning() {

	logger->logInstance = NULL;
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
}

void loggerTests::should_write_only_an_info() {

	logger->logInstance = NULL;
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
}

void loggerTests::should_be_thread_safe() {

	logger->logInstance = NULL;
	thread th1(write50Times, "1");
	thread th2(write50Times, "2");

	th1.join();
	th2.join();

	bool assert = true;
	ifstream file(logger->getLogDir());
	string line1;
	getline(file, line1);
	int i = 1;

	//me fijo que las primeras 50 lineas del archivo de log sean iguales (todas del thread 1 o todas del thread 2)
	for (std::string line2; getline(file, line2) && i < 50; i++) {

		//voy comparando una linea con la siguiente hasta la linea n° 50 (donde termina un thread y comienza el otro)
		if (line1 != line2) {
			assert = false;
			break;
		} else {
			line1 = line2;
		}
	}

	//lo mismo con las ultimas 50 lineas, si no hubo mezcla de threads continuo chequeando el otro:
	getline(file, line1);
	i++;
	for (std::string line2; getline(file, line2) && i < 100 && assert == true; i++) {

		if (line1 != line2) {
			assert = false;
			break;
		} else {
			line1 = line2;
		}
	}
	CPPUNIT_ASSERT(assert);
}

void loggerTests::should_throw_file_not_found_exception() {

	CPPUNIT_ASSERT_THROW(new Logger("invalid route"), FileNotFoundException);
}
