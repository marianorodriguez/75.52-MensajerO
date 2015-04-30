/*
 * UserConfigService.cpp
 *
 *  Created on: 29/4/2015
 *      Author: marian
 */

#include <services/UserConfigService.h>

const std::string UserConfigService::serviceName = "config";

std::string UserConfigService::getUri() const {
	return UserConfigService::serviceName;
}

void UserConfigService::executeRequest(const Connection& connection) const {

	//TODO
}

ServiceInterface* UserConfigServiceCreator::create() {
	return new UserConfigService();
}
