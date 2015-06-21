#include "../../include/main/services/LogInService.h"
#include "../../include/main/user/User.h"
#include "../../include/main/utilities/LocationManager.h"

const std::string LogInService::serviceName = SERVICE_LOGIN_NAME;

LogInService::LogInService(Database& userDb) : userDb(userDb){}

LogInService::~LogInService(){}

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


Json::Value LogInService::doLogIn(const Json::Value& data) const{

	std::vector<std::string> key;
	key.push_back(data[SERVICE_USERNAME].asString());

	Json::Value output;

	try {
		string serializedUser = userDb.read(key);
		User user(serializedUser);

			string location = LocationManager::getInstance()->getLocation(
					data[SERVICE_USERCONFIG_LOCATION].asString());
			user.modifyLocation(location);
			userDb.write(key, user.serialize());
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
	return output;
}

ServiceInterface* LogInServiceCreator::create(Database& userDb, Database& chatDb) {
	return new LogInService(userDb);
}