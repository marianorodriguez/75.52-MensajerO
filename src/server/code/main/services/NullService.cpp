#include "../../include/main/services/NullService.h"

const std::string NullService::serviceName = "";

std::string NullService::getUri() const{
	return NullService::serviceName;
}

std::string NullService::executeRequest(const Json::Value &paramMap) const{
	Logger::getLogger()->write(Logger::WARN, "Service not found.");
	return "";
}
