#include "../../include/main/services/LogOutService.h"

const std::string serviceName = SERVICE_LOGOUT_NAME;

std::string LogOutService::getUri() const {
	return serviceName;
}

std::string LogOutService::executeRequest(const Json::Value &paramMap) const {

	Json::Reader reader;
	Json::Value data;
	reader.parse(paramMap.asString(), data);

	Logger::getLogger()->write(Logger::INFO, "Executing LogOut service...");
	Json::Value output = doLogOut(data);

	return output.toStyledString();
}

Json::Value LogOutService::doLogOut(const Json::Value& data) {

	Database db(DATABASE_USERS_PATH);
	vector < string > key;
	key.push_back(data[SERVICE_USERNAME].asString());

	Json::Value output;

	try {
		string serializedUser = db.read(key);
		User user(serializedUser);

		if (user.getPassword() == data[SERVICE_PASSWORD].asString()
				&& user.getLoginToken() == data[SERVICE_TOKEN].asDouble()) {
			if (user.isLoggedIn()) {
				Logger::getLogger()->write(Logger::DEBUG,
						"User " + user.getUsername() + " has logged out.");
				user.setLoggedIn(false);
				output[SERVICE_OUT_OK] = true;
				output[SERVICE_OUT_WHAT] = "";
				db.write(key, user.serialize());
			} else {
				output[SERVICE_OUT_OK] = false;
				output[SERVICE_OUT_WHAT] = SERVICE_OUT_NOTLOGGEDUSER;
				Logger::getLogger()->write(Logger::WARN,
						"User " + user.getUsername()
								+ " tried to log out, but it's not logged in.");
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

ServiceInterface* LogOutServiceCreator::create() {
	return new LogOutService();
}
