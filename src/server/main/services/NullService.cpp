#include "NullService.h"

const std::string NullService::serviceName = "";

std::string NullService::getUri() const{
	return NullService::serviceName;
}

std::string NullService::executeRequest(const std::map<std::string, std::string> &paramMap) const{
	return "";
}
