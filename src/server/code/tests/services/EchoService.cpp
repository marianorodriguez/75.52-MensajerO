#include "../../../include/tests/services/EchoService.h"
#include "mongoose.h"

const std::string EchoService::serviceName = "echo";

std::string EchoService::getUri() const{
	return EchoService::serviceName;
}

std::string EchoService::executeRequest(const std::string &paramMap) const{
	std::string output;
	Json::Reader reader;
	Json::Value jsonMap;
	reader.parse(paramMap, jsonMap);

	for (Json::ValueIterator it = jsonMap.begin(); it != jsonMap.end(); ++it){
		std::string message(it.key().toStyledString() + " = " + jsonMap[it.key().toStyledString()].toStyledString());
		output.append(message);
	}
	return output;
}

ServiceInterface* EchoServiceCreator::create(Database& userDb, Database& chatDb){
	return new EchoService();
}
