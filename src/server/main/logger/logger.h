#ifndef LOGGER_H_
#define LOGGER_H_

#include<iostream>
#include<fstream>
#include<string.h>
#include <time.h>
#include "../config.h"
#include "json.h"
using namespace std;

/**
 * Esta clase se utiliza para registrar eventos en un archivo de texto,
 * como Errores, Advertencias, Información general y datos para Debugging.
 */
class logger {

	friend class loggerTests;

public:
/**
 *Los niveles de eventos del logger.
 */
	enum loggingLevel {
		ERROR, WARN, DEBUG, INFO,
	};

	/**
	 * Usado para llamar al logger. Si nunca antes fue llamado, se instanciará.
	 * La dirección del archivo de texto puede ser configurada en config.h
	 */
	static logger* getLogger();

	/**
	 * @param level El tipo de evento.
	 * @param text Descripcion del evento.
	 *
	 *\brief Escribe el problema en el archivo de logging.
	 */
	void write(loggingLevel level, string text);

	/**
	 * Guarda el archivo y lo vuelve a abrir.
	 */
	void saveStatus();

	/**
	 * Devuelve la dirección del archivo de logging.
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
