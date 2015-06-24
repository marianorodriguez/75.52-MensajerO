/*
 * UserConfigService.cpp
 *
 *  Created on: 29/4/2015
 *      Author: marian
 */

#include "../../../include/main/services/UserConfigService.h"

const std::string UserConfigService::serviceName = SERVICE_USERCONFIG_NAME;

UserConfigService::UserConfigService(Database& userDB) :
		userDb(userDB) {
}

std::string UserConfigService::getUri() const {
	return serviceName;
}

std::string UserConfigService::executeRequest(
		const string &paramMap) const {

	Logger::getLogger()->write(Logger::INFO, "Executing UserConfig service...");

	string output = doUserConfig(paramMap);

	return output;
}

string UserConfigService::doUserConfig(const string &data) const {

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse(data, jsonData);

	string username = jsonData[SERVICE_USERNAME].asString();
	string password = jsonData[SERVICE_PASSWORD].asString();

	std::vector<std::string> key;
	key.push_back(username);

	Json::Value output;

	try {
		string serializedUser = userDb.read(key);
		User user(serializedUser);
		if (user.getPassword() == password) {
			Logger::getLogger()->write(Logger::DEBUG,
					"updating " + username + "'s info...");
			user.modifyProfilePicture(
					jsonData[SERVICE_USERCONFIG_PICTURE].asString());
			user.modifyStatus(jsonData[SERVICE_USERCONFIG_STATUS].asString());
			userDb.write(key, user.serialize());

			output[SERVICE_OUT_OK] = true;
			output[SERVICE_OUT_WHAT] = "";
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

	ConnectionManager::getInstance()->updateUser(userDb, username);
	return output.toStyledString();
}

ServiceInterface* UserConfigServiceCreator::create(Database& userDb,
		Database& chatDb) {
	return new UserConfigService(userDb);
}
