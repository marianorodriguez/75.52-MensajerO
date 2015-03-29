#include <cppunit/config/SourcePrefix.h>
#include "loggerTests.h"
#include "../../main/logger/logger.h"
#include "../../main/utilities/stringUtil.h"
#include <stdio.h>

CPPUNIT_TEST_SUITE_REGISTRATION(loggerTests);

void loggerTests::should_be_singleton() {

	logger* logger1 = logger::getLogger();
	logger* logger2 = logger::getLogger();
	logger* logger3 = logger::getLogger();

	CPPUNIT_ASSERT(logger1 == logger2);
	CPPUNIT_ASSERT(logger2 == logger3);
	CPPUNIT_ASSERT(logger1 == logger3);
}

void loggerTests::should_instantiate_logger() {

	logger* loggerInstance = NULL;
	loggerInstance = logger::getLogger();

	CPPUNIT_ASSERT(loggerInstance != NULL);
}

void loggerTests::should_return_log_path() {

	logger* loggerInstance = logger::getLogger();
	string logDir = "";

	Json::Value json_root;
	Json::Reader json_reader;
	std::ifstream json_file(JSON_CONFIG_FILE);
	bool parsingSuccessful = json_reader.parse(json_file, json_root, false);

	if (parsingSuccessful) {
		Json::Value loggerDir = json_root["logger"];
		logDir = loggerDir.get("logDir", DEFAULT_LOGGING_FILE).asString();
	}

	CPPUNIT_ASSERT(logDir == loggerInstance->getLogDir());

}

void loggerTests::should_write_an_issue() {

//	logger* loggerInstance = logger::getLogger();
//	loggerInstance->write(logger::ERROR, "Some error");
//	string logDir = logger::getLogDir();
//	delete loggerInstance;
//
//	string shouldSay = "ERROR: Some error";
//
//	ifstream* loggerFile = new ifstream;
//	loggerFile->open(logDir.c_str(), ifstream::out);
//
//	char* buffer = new char[shouldSay.size()];
//	loggerFile->read(buffer, shouldSay.size());
//
//	CPPUNIT_ASSERT(buffer == shouldSay.c_str());
//
//	delete loggerFile;
}

void loggerTests::should_stamp_time_and_date() {

}

void loggerTests::should_return_loggingLevels() {

	CPPUNIT_ASSERT(
			logger::getLogger()->getWriteLevel(logger::ERROR) == "ERROR");
	CPPUNIT_ASSERT(
			logger::getLogger()->getWriteLevel(logger::WARN) == "WARNING");
	CPPUNIT_ASSERT(logger::getLogger()->getWriteLevel(logger::INFO) == "INFO");
	CPPUNIT_ASSERT(
			logger::getLogger()->getWriteLevel(logger::DEBUG) == "DEBUG");

}

void loggerTests::should_set_logging_levels() {

}
