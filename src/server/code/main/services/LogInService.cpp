#include "../../include/main/services/LogInService.h"
const std::string LogInService::serviceName = SERVICE_LOGIN_NAME;

std::string LogInService::getUri() const {
	return LogInService::serviceName;
}

std::string LogInService::executeRequest(
		const std::map<std::string, std::string> &paramMap) const {

	Json::Value data;
	data[SERVICE_USERNAME] = paramMap.at(SERVICE_USERNAME);
	data[SERVICE_PASSWORD] = paramMap.at(SERVICE_PASSWORD);
	data[SERVICE_USERCONFIG_LOCATION] = paramMap.at(
			SERVICE_USERCONFIG_LOCATION);

	Json::Value output = doLogIn(data);

	ConnectionManager::getInstance()->updateUser(
			data[SERVICE_USERNAME].asString());
	return output.toStyledString();
}

ServiceInterface* LogInServiceCreator::create() {
	return new LogInService();
}

Json::Value LogInService::doLogIn(const Json::Value& data) {

	Database db(DATABASE_USERS_PATH);
	vector<string> key;
	key.push_back(data[SERVICE_USERNAME].asString());

	Json::Value output;

	try {
		string serializedUser = db.read(key);
		User user(serializedUser);

		if (user.getPassword() == data[SERVICE_PASSWORD].asString()) {
			output[SERVICE_USERCONFIG_LOCATION] = LocationManager::getLocation(
					data[SERVICE_USERCONFIG_LOCATION].asString());
			output[SERVICE_USERCONFIG_STATUS] = user.getStatus();
			output[SERVICE_USERCONFIG_PICTURE] = user.getProfilePicture();
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
