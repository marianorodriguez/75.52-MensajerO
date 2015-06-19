#include <../../../include/main/services/UsersService.h>

const std::string serviceName = SERVICE_USERS_NAME;

std::string UsersService::getUri() const {
	return serviceName;
}

std::string UsersService::executeRequest(const Json::Value &paramMap) const {

	Json::Reader reader;
	Json::Value data;
	reader.parse(paramMap.asString(), data);
	Logger::getLogger()->write(Logger::INFO,
			"Executing Users service...");
	Json::Value output = doUsers(data);

	ConnectionManager::getInstance()->updateUser(
			data[SERVICE_USERNAME].asString());

	return output.toStyledString();
}

Json::Value UsersService::doUsers(const Json::Value &data) {

	Database DB(DATABASE_USERS_PATH);

	Json::Value output;

	try {

		std::vector<std::string> key;
		key.push_back(data[SERVICE_USERNAME].asString());
		std::string userValue = DB.read(key);
		User user(userValue);

		if (data[SERVICE_PASSWORD].asString() == user.getPassword()) {

			Logger::getLogger()->write(Logger::DEBUG,
					"Fetching all users in database...");
			vector<string> keys = DB.getAllKeys();
			vector<string> key;

			for (unsigned int i = 0; i < keys.size(); i++) {
				key.push_back(keys.at(i));
				output["users"][i] = DB.read(key);
				key.clear();
			}

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

	DB.close();
	return output;
}

ServiceInterface* UsersServiceCreator::create() {
	return new UsersService();
}
