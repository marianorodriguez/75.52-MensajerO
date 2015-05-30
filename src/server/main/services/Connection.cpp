#include <map>
#include "mongoose.h"

#include "Connection.h"
#include "QueryParams.h"
#include "utilities/JsonMap.h"
#include "utilities/Base64.h"
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

std::map<std::string, std::string> Connection::getParamMap() const{
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

		QueryParams params(query);
		this->paramMap = params.getParams();
	}
}

void Connection::parsePostParams(){
	//TODO mlafroce: hacer más genérico
	
	if (this->rawConnection->content){
		// TODO mlafroce: verificar si es un bug de mongoose
		std::string content;
		content.assign(this->rawConnection->content,
					 this->rawConnection->content_len);
		std::string prefix("package=");
		content = content.substr(prefix.length());
		std::string decodedContent = base64::decode(content);
		std::cout<<"post: "<<decodedContent<<std::endl;
		JsonMap jsonMap(decodedContent);

		this->paramMap = jsonMap.getMap();
	}
}

