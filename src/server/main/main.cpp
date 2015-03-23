#include "logger/logger.h"
#include <iostream>

using namespace std;

int main() {

	logger* log = logger::getLogger();

	log->write(logger::ERROR, "Error desconocido.");
	log->write(logger::DEBUG, "la variable vale 3.");
	log->write(logger::INFO, "Info de app.");
	log->write(logger::WARN, "cuidado! valor no establecido.");
	log->saveStatus();

	delete log;
	return 0;
}
