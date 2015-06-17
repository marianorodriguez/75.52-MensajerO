#include <map>
#include "mongoose.h"

#include "../../include/main/services/Connection.h"
#include "../../include/main/services/QueryParams.h"
#include "../../include/main/utilities/JsonMap.h"
#include "../../include/main/utilities/Base64.h"
#include <iostream>

// Constantes
const std::string Connection::getMethodName = "GET";
const std::string Connection::postMethodName = "POST";

Connection::Connection(mg_connection* const rawConnection){
	this->rawConnection = rawConnection;
	const char* requestType = rawConnection->request_method;

	if (!requestType){
		throw "No request type specified"; 
	}
	// TODO instanciar una strategy según tipo de request
	if (Connection::getMethodName.
		compare(rawConnection->request_method) == 0){
		parseGetParams();
	} else if (Connection::postMethodName.
		compare(rawConnection->request_method) == 0){
		parsePostParams();
	}
}

std::string Connection::getUri() const{
	return this->rawConnection->uri;
}

mg_connection* Connection::getRawConnection() const{
	return this->rawConnection;
}

Json::Value Connection::getParamMap() const{
	return this->paramMap;
}

void Connection::printMessage(const std::string& message) const{
	std::string data = base64::encode((unsigned char*)(message.c_str()),
									  message.length());
	mg_printf_data(this->rawConnection, data.c_str());
}

void Connection::parseGetParams(){
	this->paramMap.clear();
	if (this->rawConnection->query_string){
		std::string query(this->rawConnection->query_string);

		Json::Value params(base64::decode(query));
		this->paramMap = params;
	}
}

void Connection::parsePostParams(){
	//TODO mlafroce: hacer más genérico
	
	if (this->rawConnection->content_len){
		// TODO mlafroce: verificar si es un bug de mongoose
		std::string content;
		content.assign(this->rawConnection->content, this->rawConnection->content_len);
		std::string package = "package=";
		content = content.substr(package.size(), content.size());
		Json::Value jsonMap(base64::decode(content));

		this->paramMap = jsonMap;
	}
}
