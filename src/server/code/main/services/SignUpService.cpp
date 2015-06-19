#include "../../../include/main/services/SignUpService.h"

const std::string serviceName = SERVICE_SIGNUP_NAME;

std::string SignUpService::getUri() const {
	return serviceName;
}

std::string SignUpService::executeRequest(const Json::Value &paramMap) const {

	Json::Reader reader;
	Json::Value data;
	reader.parse(paramMap.asString(), data);
	Logger::getLogger()->write(Logger::INFO, "Executing SignUp service...");
	Json::Value output = doSignUp(data);
	ConnectionManager::getInstance()->updateUser(
			data[SERVICE_USERNAME].asString());

	return output.toStyledString();
}

bool checkUsernameExists(const std::string& username) {

	bool exists = false;
	Database DB(DATABASE_USERS_PATH);
	vector<string> key;
	key.push_back(username);

	try {
		std::string value = DB.read(key);
		exists = true;
	} catch (KeyNotFoundException &e) {
	}

	DB.close();
	return exists;
}

ServiceInterface* SignUpServiceCreator::create() {
	return new SignUpService();
}

Json::Value SignUpService::doSignUp(const Json::Value& data) {

	//si no hay error, guardo el usuario en la BD y devuelvo OK

	bool exists = checkUsernameExists(data[SERVICE_USERNAME].asString());

	Json::Value output;

	if (!exists) {
		Logger::getLogger()->write(Logger::DEBUG, "Registering new user...");
		Database DB(DATABASE_USERS_PATH);
		std::string username = data[SERVICE_USERNAME].asString();
		std::string password = data[SERVICE_PASSWORD].asString();
		User newUser(username, password);

		newUser.modifyStatus(data[SERVICE_USERCONFIG_STATUS].asString());
		newUser.modifyLocation(
				LocationManager::getLocation(
						data[SERVICE_USERCONFIG_LOCATION].asString()));
		newUser.modifyProfilePicture(
				data[SERVICE_USERCONFIG_PICTURE].asString());

		std::vector<std::string> key;
		key.push_back(username);
		DB.write(key, newUser.serialize());

		//le envio sus datos al user como confirmacion
		output[SERVICE_USERCONFIG_LOCATION] = newUser.getLocation();
		output[SERVICE_OUT_OK] = true;
		output[SERVICE_OUT_WHAT] = "";
		Logger::getLogger()->write(Logger::DEBUG,
				"user " + data[SERVICE_USERNAME].asString()
						+ " successfully registered.");
		DB.close();
	} else {
		output[SERVICE_OUT_OK] = false;
		output[SERVICE_OUT_WHAT] = SERVICE_OUT_USERNAMEEXISTS;
		Logger::getLogger()->write(Logger::DEBUG,
				"Couldn't register user " + data[SERVICE_USERNAME].asString());
	}

	return output;
}
