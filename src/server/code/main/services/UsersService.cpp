#include <../../../include/main/services/UsersService.h>

const std::string UsersService::serviceName = SERVICE_USERS_NAME;

UsersService::UsersService(Database& users): userDb(users){

}

std::string UsersService::getUri() const {
	return serviceName;
}

std::string UsersService::executeRequest(const string &paramMap) const {

	Logger::getLogger()->write(Logger::INFO,
			"Executing Users service...");

	string output = doUsers(paramMap);

	return output;
}

string UsersService::doUsers(const string &data) const {

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse(data, jsonData);

	string username = jsonData[SERVICE_USERNAME].asString();
	string password = jsonData[SERVICE_PASSWORD].asString();
	Json::Value output;

	try {

		std::vector<std::string> key;
		key.push_back(username);
		std::string userValue = userDb.read(key);
		User user(userValue);

		if (user.getPassword() == password) {

			Logger::getLogger()->write(Logger::DEBUG,
					"Fetching all users in database...");
			vector<string> keys = userDb.getAllKeys();
			vector<string> key;

			for (unsigned int i = 0; i < keys.size(); i++) {
				key.push_back(keys.at(i));
				output["users"][i] = userDb.read(key);
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

	ConnectionManager::getInstance()->updateUser(userDb, username);
	return output.toStyledString();
}

ServiceInterface* UsersServiceCreator::create(Database& userDb, Database& chatDb) {
	return new UsersService(userDb);
}
