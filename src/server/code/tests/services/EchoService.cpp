#include "../../../include/tests/services/EchoService.h"
#include "mongoose.h"

const std::string EchoService::serviceName = "echo";

std::string EchoService::getUri() const{
	return EchoService::serviceName;
}

std::string EchoService::executeRequest(const Json::Value &paramMap) const{
	std::string output;

	for (Json::ValueIterator it = paramMap.begin(); it != paramMap.end(); ++it){
		std::string message(it.key().toStyledString() + " = " + paramMap[it.key().toStyledString()].toStyledString());
		output.append(message);
	}
	return output;
}

ServiceInterface* EchoServiceCreator::create(Database& userDb, Database& chatDb){
	return new EchoService();
}
