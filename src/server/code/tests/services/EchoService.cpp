#include "../../../include/tests/services/EchoService.h"
#include "mongoose.h"

const std::string EchoService::serviceName = "echo";

std::string EchoService::getUri() const{
	return EchoService::serviceName;
}

std::string EchoService::executeRequest(const std::map< std::string, std::string >& paramMap) const{
	std::string output;
	std::map<std::string, std::string>::const_iterator it;
	for (it = paramMap.begin(); it != paramMap.end(); ++it){
		std::string message(it->first + " = " + it->second);
		output.append(message);
	}
	return output;
}

ServiceInterface* EchoServiceCreator::create(){
	return new EchoService();
}
