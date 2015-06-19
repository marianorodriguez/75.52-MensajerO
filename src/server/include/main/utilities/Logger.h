#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>
#include <string.h>
#include "../config.h"
#include "../exceptions/FileNotFoundException.h"
#include "Mutex.h"
#include "Date.h"
#include "Time.h"
#include <json-forwards.h>

using namespace std;

/**
 * Esta clase se utiliza para registrar eventos en un archivo de texto,
 * como Errores, Advertencias, Información general y datos para Debugging.
 */
class Logger {

	friend class LoggerTest;

public:
	/**
	 *Los niveles de eventos del logger.
	 *ERROR: Para eventos que lanzan una excepción.
	 *WARNING: Para eventos en donde no se pudo completar un pedido u ocurrió algo poco usual, pero no se lanzó excepcion.
	 *INFO: Para dejar constancia de eventos importantes.
	 *DEBUG: Para facilitar el hallazgo de bugs sin necesidad de recompilar el código, o extender la informacion de INFO.
	 */
	enum loggingLevel {
		ERROR, WARN, DEBUG, INFO,
	};

	/**
	 * Usado para llamar al logger. Si nunca antes fue llamado, se instanciará.
	 * La dirección del archivo de texto puede ser configurada en config.h
	 */
	static Logger* getLogger();

	/**
	 * Usado para llamar al logger. Si nunca antes fue llamado, se instanciará.
	 * La dirección del archivo de texto puede ser configurada en config.h
	 */
	static void destroy();

	/**
	 * @param level El tipo de evento.
	 * @param text Descripcion del evento.
	 *
	 *\brief Escribe el problema en el archivo de logging.
	 */
	void write(loggingLevel level, string text);

	/**
	 * Escribe el buffer al archivo de logging.
	 */
	void saveStatus();

	/**
	 * Devuelve la dirección del archivo de logging.
	 */
	static string getLogDir();

	~Logger();

private:

	bool levels[4];
	static Logger* logInstance;
	ofstream file;
	static string logDir;

	Logger(const std::string& loggerDir);
	string getWriteLevel(const loggingLevel& level);
	void setLoggingLevels(const Json::Value& jsonLogger);

	Mutex mutex;
	static Mutex constructorMutex;
};

#endif /* LOGGER_H_ */
