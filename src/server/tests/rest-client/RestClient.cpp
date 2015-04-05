#include "RestClient.h"
#include <sstream>
#include <curl/curl.h>

RestClient::RestClient(){
	this->curl = curl_easy_init();
	if (!this->curl){
		throw "Client not initiated";
	}
	// Preparo la función de callback
	curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, RestClient::callback);
	curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, this);
}

RestClient::~RestClient(){
	curl_easy_cleanup(this->curl);
}

// TODO: multithread
std::string RestClient::execute(RestClient::RequestType requestType, const RestQuery& query){
	CURLcode res;
	switch(requestType){
	case GET:
		curl_easy_setopt(curl, CURLOPT_URL, query.buildGetQuery().c_str());
		break;
	default:
		break;
	}
	this->response.clear();
	res = curl_easy_perform(curl);
	if (res == CURLE_OK) {
		return this->response;
	} else {
		throw "Error al obtener respuesta";
	}
}

size_t RestClient::callback(void* contents, size_t size, size_t nmemb, void* data){
	size_t realsize = size * nmemb;
	RestClient *client = static_cast<RestClient*>(data);
	client->response.append(static_cast<char*>(contents), realsize);
	return realsize;
}

/**
 * Clase auxiliar para armar querys
 */

void RestQuery::setBaseUri(const std::string& baseUri){
	this->baseUri = baseUri;
}

void RestQuery::setParameter(const std::string& key, const std::string& value){
	this->parameters[key] = value;
}

std::string RestQuery::buildGetQuery() const{
	std::stringstream paramStream;
	paramStream << "?";
	std::map<std::string, std::string>::const_iterator it = this->parameters.begin();
	for (;it != parameters.end(); ++it) {
		paramStream << it->first << "=" << it->second << "&";
	}
	// Quito la última letra
	std::string paramString = paramStream.str();
	paramString = paramString.substr(0, paramString.size()-1);
	return this->baseUri + paramString; 
}
