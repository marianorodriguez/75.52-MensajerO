#ifndef LOGGER_H_
#define LOGGER_H_

#include<iostream>
#include<fstream>
#include<string.h>
#include <time.h>
#include "../config.h"
#include "../jsoncpp/json.h"
using namespace std;

/**
 * This class is used to log run-time issues, like Errors, Warnings, Info and Debugging.
 */
class logger {

	friend class loggerTests;

public:
/**
 *The level of the logger.
 */
	enum loggingLevel {
		ERROR, WARN, DEBUG, INFO,
	};

	/**
	 * Used to call the logger instance. If it doesn't exists, it will be instantiated.
	 * The path to the logging file can be configured in the config.h
	 */
	static logger* getLogger();

	/**
	 * @param level The Level of the issue.
	 * @param text Description of the issue.
	 *
	 *\brief Writes the issue into a file.
	 */
	void write(loggingLevel level, string text);

	/**
	 * Saves the file and re-opens it.
	 */
	void saveStatus();

	/**
	 * Returns the path to the logging file.
	 */
	static string getLogDir();

	~logger();

private:

	Json::Value json_logger;
	bool levels[4];
	static logger* logInstance;
	ofstream* file;
	static string logDir;

	logger();
	void dateStamp();
	string getWriteLevel(loggingLevel level);
	void setLoggingLevels();
};

#endif /* LOGGER_H_ */
