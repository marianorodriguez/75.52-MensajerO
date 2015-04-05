#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include <string>
#include <map>

// Forwards
class RestQuery;

class RestClient{
public:
	enum RequestType {GET, POST};
	/**
	 * Constructor
	 */
	RestClient();
	/**
	 * Destructor
	 */
	~RestClient();
	/**
	 * Ejecuta un request y devuelve el response
	 * TODO: multithread
	 */
	std::string execute(RestClient::RequestType requestType, const RestQuery& query);
	/**
	 * Función que se llama cuando ejecuto un request, para
	 * procesar el resultado de la ejecución.
	 */
	static size_t callback(void *contents, size_t size, size_t nmemb, void *data);
private:
	void* curl;
	std::string response;
	/**
	 * Agrega al buffer del ciente la respuesta que recibió de ejecutar
	 * un request
	 */
	//void appendResponse(void* contents, size_t realsize);
};

/**
 * Clase para armar querys de rest
 */
class RestQuery{
public:
	/**
	 * Indica cual es la dirección del recurso
	 */
	void setBaseUri(const std::string& baseUri);
	/**
	 * Agrega parámetros al request
	 */
	void setParameter(const std::string& key, const std::string& value);
	/**
	 * Devuelve la uri con parametros para realizar un get
	 */
	std::string buildGetQuery() const;
private:
	std::string baseUri;
	std::map<std::string, std::string> parameters;
};

#endif // RESTCLIENT_H
