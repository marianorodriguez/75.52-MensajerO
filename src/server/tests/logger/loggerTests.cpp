#include <cppunit/config/SourcePrefix.h>
#include "loggerTests.h"
#include "../../main/logger/logger.h"
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
	//todo completar prueba
	CPPUNIT_ASSERT(false);
}

void loggerTests::should_stamp_time_and_date() {
	//todo completar prueba
	CPPUNIT_ASSERT(false);
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
	//TODO completar prueba
	CPPUNIT_ASSERT(false);
}

void loggerTests::should_throw_file_not_found_exception(){

	//TODO hacer alguna magia para que no pueda encontrar el archivo config.json
	CPPUNIT_ASSERT(false);
}
