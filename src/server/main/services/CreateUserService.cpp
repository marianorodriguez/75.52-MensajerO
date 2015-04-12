#include "CreateUserService.h"

const std::string CreateUserService::serviceName = "createUser";

std::string CreateUserService::getUri() const{
	return CreateUserService::serviceName;
}

void CreateUserService::executeRequest(const Connection& connection) const{
}
