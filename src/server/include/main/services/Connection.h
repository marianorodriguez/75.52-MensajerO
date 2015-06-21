#ifndef CONNECTION_H
#define CONNECTION_H

#include <map>
#include <string>
#include "json.h"
#include "../../../include/main/utilities/Logger.h"

// Forwards
struct mg_connection;

/**
 * Clase que engloba una conexión mongoose.
 */
class Connection {
	friend class ServicesIntegrationTests;
public:
	/**
	 * Constructor
	 * @param rawConnection conexión mongoose con el request
	 */
	Connection(mg_connection* const rawConnection);
	/**
	 * Devuelve la uri de la conexión
	 */
	std::string getUri() const;
	/**
	 * Devuelve la conexión mongoose a la que representa
	 */
	mg_connection* getRawConnection() const;
	/**
	 * Le envía un mensaje al cliente que realizó el request
	 */
	void printMessage(const std::string& message) const;
	/**
	 * Devuelve un mapa con los parámetros recibidos por request
	 */
	Json::Value getParamMap() const;
private:
	/**
	 * Conexión mongoose con los datos del request y cliente
	 */
	mg_connection* rawConnection;

	Json::Value paramMap;
	static const std::string getMethodName;
	static const std::string postMethodName;
	// TODO mlafroce: usar strategy
	void parseGetParams();
	void parsePostParams();
};

#endif // CONNECTION_H
