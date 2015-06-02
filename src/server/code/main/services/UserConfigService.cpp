/*
 * UserConfigService.cpp
 *
 *  Created on: 29/4/2015
 *      Author: marian
 */

#include "../../../include/main/services/UserConfigService.h"

const std::string UserConfigService::serviceName = SERVICE_USERCONFIG_NAME;

std::string UserConfigService::getUri() const {
	return UserConfigService::serviceName;
}

std::string UserConfigService::executeRequest(
		const Json::Value &paramMap) const {

	Json::Reader reader;
	Json::Value data;
	reader.parse(paramMap.asString(), data);
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
		if (user.getPassword() == data[SERVICE_PASSWORD].asString()) {
			user.modifyProfilePicture(
					data[SERVICE_USERCONFIG_PICTURE].asString());
			user.modifyStatus(data[SERVICE_USERCONFIG_STATUS].asString());
			db.write(key, user.serialize());

			output[SERVICE_OUT_OK] = true;
			output[SERVICE_OUT_WHAT] = "";
		} else {
			output[SERVICE_OUT_OK] = false;
			output[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDPWD;
		}
	} catch (KeyNotFoundException &e) {
		output[SERVICE_OUT_OK] = false;
		output[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDUSER;
	}

	return output;
}

ServiceInterface* UserConfigServiceCreator::create() {
	return new UserConfigService();
}
