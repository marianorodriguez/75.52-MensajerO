#include "../../include/main/utilities/Time.h"
#include <ctime>
#include <cstring>

std::string Time::getTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];

	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%X", &tstruct);

	std::string hour;
	std::string min;
	unsigned int i;

	for (i = 0; (i < strlen(buf)) && (buf[i] != ':'); i++) {
		hour += buf[i];
	}

	for (unsigned int j = i + 1; (j < strlen(buf)) && (buf[j] != ':'); j++) {
		min += buf[j];
	}

	return hour + ":" + min;
}
