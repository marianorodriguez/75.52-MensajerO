#include "../../include/main/utilities/Date.h"
#include <ctime>
#include <cstring>

std::string Date::getDate() {

	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%d/%m/%Y", &tstruct);
	return buf;
}
