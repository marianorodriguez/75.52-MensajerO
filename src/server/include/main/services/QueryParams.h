#ifndef QUERYPARAMS_H
#define QUERYPARAMS_H

#include <map>
#include <string>

class QueryParams{
public:
	/**
	 * Toma una lista de parametros y lo convierte en un mapa
	 */
	QueryParams(const std::string& paramString);
	/**
	 * Devuelve un mapa de los parametros obtenidos
	 */
	std::map<std::string, std::string>& getParams();
private:
	/**
	 * Separa parametros divididos por un token
	 */
	void parseParams(const std::string& paramString);
	/**
	 * Separa el par clave valor de un parametro
	 */
	void parseKeyValue(const std::string& param);
	/**
	 * Mapa de parametros
	 */
	std::map<std::string, std::string> params;
	/**
	 * Separador de parametros
	 */
	static const std::string kParamToken;
	/**
	 * Separador de clave - valor
	 */
	static const std::string kKeyValueToken;
};

#endif // QUERYPARAMS_H
