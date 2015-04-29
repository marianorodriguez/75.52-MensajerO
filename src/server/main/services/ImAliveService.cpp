/*
 * ImAliveService.cpp
 *
 *  Created on: 29/4/2015
 *      Author: marian
 */

#include <services/ImAliveService.h>

const std::string ImAliveService::serviceName = SERVICE_IMALIVE_NAME;

ImAliveService::ImAliveService() {}

ImAliveService::~ImAliveService() {}

std::string ImAliveService::getUri() const{
	return ImAliveService::serviceName;
}

void ImAliveService::executeRequest(const Connection& connection) const{

	std::string username = connection.getParamMap()[SERVICE_USERNAME];

	ConnectionManager::getInstance()->updateUser(username);
}

ServiceInterface* ImAliveServiceCreator::create(){
	return new ImAliveService();
}
