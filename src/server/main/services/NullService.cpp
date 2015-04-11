#include "NullService.h"

const std::string NullService::serviceName = "";

std::string NullService::getUri() const{
	return NullService::serviceName;
}

void NullService::executeRequest(const Connection& connection) const{
	throw "Service not implemented";
}