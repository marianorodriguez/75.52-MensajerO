/*
 * UserConfigService.cpp
 *
 *  Created on: 29/4/2015
 *      Author: marian
 */

#include "../../../include/main/services/UserConfigService.h"

const std::string serviceName = SERVICE_USERCONFIG_NAME;

std::string UserConfigService::getUri() const {
	return serviceName;
}

std::string UserConfigService::executeRequest(
		const Json::Value &paramMap) const {

	Json::Reader reader;
	Json::Value data;
	reader.parse(paramMap.asString(), data);
	Logger::getLogger()->write(Logger::INFO, "Executing UserConfig service...");
	Json::Value output = doUserConfig(data);
	ConnectionManager::getInstance()->updateUser(
			data[SERVICE_USERNAME].asString());

	return output.toStyledString();
}

Json::Value UserConfigService::doUserConfig(const Json::Value &data) {

	Database db(DATABASE_USERS_PATH);
	std::vector<std::string> key;
	key.push_back(data[SERVICE_USERNAME].asString());

	Json::Value output;

	try {
		string serializedUser = db.read(key);
		User user(serializedUser);
		if (user.getPassword() == data[SERVICE_PASSWORD].asString()
				&& user.getLoginToken() == data[SERVICE_TOKEN].asDouble()) {
			if (user.isLoggedIn()) {
				Logger::getLogger()->write(Logger::DEBUG,
						"updating " + user.getUsername() + "'s info...");
				user.modifyProfilePicture(
						data[SERVICE_USERCONFIG_PICTURE].asString());
				user.modifyStatus(data[SERVICE_USERCONFIG_STATUS].asString());
				db.write(key, user.serialize());

				output[SERVICE_OUT_OK] = true;
				output[SERVICE_OUT_WHAT] = "";
			} else {
				output[SERVICE_OUT_OK] = false;
				output[SERVICE_OUT_WHAT] = SERVICE_OUT_NOTLOGGEDUSER;
				Logger::getLogger()->write(Logger::WARN,
						"User " + user.getUsername() + " is not logged in.");
			}
		} else {
			output[SERVICE_OUT_OK] = false;
			output[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDPWD;
			Logger::getLogger()->write(Logger::WARN,
					"Invalid password from user " + user.getUsername());
		}
	} catch (KeyNotFoundException &e) {
		output[SERVICE_OUT_OK] = false;
		output[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDUSER;
		Logger::getLogger()->write(Logger::WARN,
				"Some unregistered user tried to use this service.");
	}

	db.close();
	return output;
}

ServiceInterface* UserConfigServiceCreator::create() {
	return new UserConfigService();
}
