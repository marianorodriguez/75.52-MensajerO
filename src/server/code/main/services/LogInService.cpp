#include "../../include/main/services/LogInService.h"
#include "../../include/main/user/User.h"
#include "../../include/main/utilities/LocationManager.h"

const std::string LogInService::serviceName = SERVICE_LOGIN_NAME;

LogInService::LogInService(Database& userDb) : userDb(userDb){}

LogInService::~LogInService(){}

std::string LogInService::getUri() const {
	return serviceName;
}

std::string LogInService::executeRequest(const string &paramMap) const {

	Logger::getLogger()->write(Logger::INFO,
			"Executing LogIn service...");

	string output = doLogIn(paramMap);

	return output;
}


string LogInService::doLogIn(const string& data) const{

	Json::Value jsonIn;
	Json::Reader reader;
	reader.parse(data, jsonIn);
	string username = jsonIn[SERVICE_USERNAME].asString();
	string password = jsonIn[SERVICE_PASSWORD].asString();

	std::vector<std::string> key;
	key.push_back(username);

	Json::Value output;

	try {
		string serializedUser = userDb.read(key);
		User user(serializedUser);

			string location = LocationManager::getInstance()->getLocation(
					jsonIn[SERVICE_USERCONFIG_LOCATION].asString());
			user.modifyLocation(location);
			userDb.write(key, user.serialize());
		if (user.getPassword() == password) {
			Logger::getLogger()->write(Logger::DEBUG, "Granting access to user " + username);
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

	ConnectionManager::getInstance()->updateUser(this->userDb, username);
	return output.toStyledString();
}

ServiceInterface* LogInServiceCreator::create(Database& userDb, Database& chatDb) {
	return new LogInService(userDb);
}
