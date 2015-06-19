#include "../../include/main/services/NullService.h"

const std::string serviceName = "";

std::string NullService::getUri() const{
	return serviceName;
}

std::string NullService::executeRequest(const Json::Value &paramMap) const{
	Logger::getLogger()->write(Logger::WARN, "Someone tried to invoke an unknown service.");
	return "";
}
