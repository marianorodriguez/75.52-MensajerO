#include <cppunit/config/SourcePrefix.h>
#include "LoggerTest.h"
#include <stdio.h>
#include "utilities/Logger.h"

CPPUNIT_TEST_SUITE_REGISTRATION(LoggerTest);

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

void LoggerTest::should_be_thread_safe() {

	thread th1(write50Times, "1");
	thread th2(write50Times, "2");
	thread th3(write50Times, "3");
	thread th4(write50Times, "4");

	th1.join();
	th2.join();
	th3.join();
	th4.join();

	bool assert = false;
	ifstream file(logger->getLogDir());

	string line;
	getline(file, line);

	//veo si la primer linea es del thread 1 o del thread 2
	size_t foundth1 = line.find("thread n1");
	size_t foundth2 = line.find("thread n2");

	if (foundth1 != string::npos && foundth2 == string::npos) { //si se encontró el thread 1, me aseguro que las siguientes 49 lineas sean del mismo thread

		for (int i = 1; i < 50; i++) {
			getline(file, line);
			foundth1 = line.find("thread n1");
			if (foundth1 == string::npos) {
				assert = false;
				break;
			} else {
				assert = true;
			}
		}

		for (int i = 50; i < 100 && assert == true; i++) {	//las lineas 50 a 100 tienen que ser del thread n2
			getline(file, line);
			foundth2 = line.find("thread n2");
			if (foundth2 == string::npos) {
				assert = false;
				break;
			} else {
				assert = true;
			}
		}
	} else {	//lo mismo pero al reves

		for (int i = 1; i < 50; i++) {
			getline(file, line);
			foundth2 = line.find("thread n2");
			if (foundth2 == string::npos) {
				assert = false;
				break;
			} else {
				assert = true;
			}
		}

		for (int i = 50; i < 100; i++) {	//las lineas 50 a 100 tienen que ser del thread n1
			getline(file, line);
			foundth1 = line.find("thread n1");
			if (foundth1 == string::npos) {
				assert = false;
				break;
			} else {
				assert = true;
			}
		}
	}

	CPPUNIT_ASSERT(assert);

	delete logger;
}

void LoggerTest::should_throw_file_not_found_exception() {

	CPPUNIT_ASSERT_THROW(new Logger("invalid route"), FileNotFoundException);
}
