/*
 * UserConfigService.cpp
 *
 *  Created on: 29/4/2015
 *      Author: marian
 */

#include <services/UserConfigService.h>

const std::string UserConfigService::serviceName = SERVICE_USERCONFIG_NAME;

std::string UserConfigService::getUri() const {
	return UserConfigService::serviceName;
}

void UserConfigService::executeRequest(const Connection& connection) const {

	string username = connection.getParamMap()[SERVICE_USERNAME];
	string password = connection.getParamMap()[SERVICE_PASSWORD];
	string location = connection.getParamMap()[SERVICE_USERCONFIG_LOCATION];
	string status = connection.getParamMap()[SERVICE_USERCONFIG_STATUS];
	string picture = connection.getParamMap()[SERVICE_USERCONFIG_PICTURE];

	Database db(DATABASE_USERS_PATH);
	vector<string> key;
	key.push_back(username);

	try {
		string serializedUser = db.read(key);
		User user(serializedUser);
		if (user.getPassword() == password) {
			user.modifyLocation(location);
			user.modifyProfilePicture(picture);
			user.modifyStatus(status);
			db.write(key,user.serialize());
			connection.printMessage("Ok");
			return;
		} else {
			connection.printMessage("Error: Contraseña incorrecta");
		}
	} catch (KeyNotFoundException &e) {
		connection.printMessage("Error: Usuario incorrecto");
	}
}

ServiceInterface* UserConfigServiceCreator::create() {
	return new UserConfigService();
}
