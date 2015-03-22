#ifndef LOGGER_H_
#define LOGGER_H_

#include<iostream>
#include<fstream>
#include<string.h>
#include <time.h>
#include "../config.h"
#include "../jsoncpp/json.h"
using namespace std;

class logger {

public:
	enum loggingLevel {
		ERROR, WARN, DEBUG, INFO,
	};

	static logger* getLogger();
	void write(loggingLevel level, string text);
	void saveStatus();
	~logger();

private:

	Json::Value json_logger;
	bool levels[4];
	static logger* logInstance;
	ofstream* file;
	string logDir;

	logger();
	void dateStamp();
	string getWriteLevel(loggingLevel level);
	void setLoggingLevels();
};

#endif /* LOGGER_H_ */
