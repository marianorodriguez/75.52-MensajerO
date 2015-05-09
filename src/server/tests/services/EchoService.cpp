#include "EchoService.h"
#include "mongoose.h"

const std::string EchoService::serviceName = "echo";

std::string EchoService::getUri() const{
	return EchoService::serviceName;
}

void EchoService::executeRequest(const Connection& connection) const{
	std::string uri(connection.getUri());
	connection.printMessage(uri);
	std::map<std::string, std::string>::const_iterator it;
	std::map<std::string, std::string> paramMap;
	paramMap = connection.getParamMap();
	for (it = paramMap.begin(); it != paramMap.end(); ++it){
		std::string message(it->first + " = " + it->second);
		connection.printMessage(message);
	}
}

ServiceInterface* EchoServiceCreator::create(){
	return new EchoService();
}
