#include "EchoService.h"
#include "mongoose.h"

const std::string EchoService::serviceName = "echo";

std::string EchoService::getUri() const{
	return EchoService::serviceName;
}

void EchoService::executeRequest(const Connection& connection) const{
	std::string uri(connection.getUri());
	mg_printf_data(connection.getRawConnection(), uri.c_str());
}
