#include "Date.h"

Date::Date() {
}

Date::~Date() {
}

string Date::getDate() {

	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%d/%m/%Y", &tstruct);
	return buf;
}
