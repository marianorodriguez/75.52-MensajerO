#include "../../include/main/services/LogInService.h"
const std::string serviceName = SERVICE_LOGIN_NAME;

std::string LogInService::getUri() const {
	return serviceName;
}

std::string LogInService::executeRequest(const Json::Value &paramMap) const {

	Json::Reader reader;
	Json::Value data;
	reader.parse(paramMap.asString(), data);

	Logger::getLogger()->write(Logger::INFO,
			"Executing LogIn service...");
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

			string location = LocationManager::getInstance()->getLocation(
					data[SERVICE_USERCONFIG_LOCATION].asString());
			user.modifyLocation(location);
			db.write(key, user.serialize());
		if (user.getPassword() == data[SERVICE_PASSWORD].asString()) {
			Logger::getLogger()->write(Logger::DEBUG, "Granting access to user " + user.getUsername());
			output[SERVICE_USERCONFIG_LOCATION] = location;
			output[SERVICE_USERCONFIG_STATUS] = user.getStatus();
			output[SERVICE_USERCONFIG_PICTURE] = user.getProfilePicture();
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
		Logger::getLogger()->write(Logger::WARN, "Some unregistered user tried to use this service.");

	}
	db.close();
	return output;
}
