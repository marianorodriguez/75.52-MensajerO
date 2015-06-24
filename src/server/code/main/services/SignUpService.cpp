#include "../../../include/main/services/SignUpService.h"

const std::string SignUpService::serviceName = SERVICE_SIGNUP_NAME;

SignUpService::SignUpService(Database& userDb) :
		userDb(userDb) {
}

std::string SignUpService::getUri() const {
	return serviceName;
}

std::string SignUpService::executeRequest(const string &paramMap) const {

	Logger::getLogger()->write(Logger::INFO, "Executing SignUp service...");

	string output = doSignUp(paramMap);

	return output;
}

bool SignUpService::checkUsernameExists(const std::string& username) const {

	bool exists = false;
	vector<string> key;
	key.push_back(username);

	try {
		std::string value = this->userDb.read(key);
		exists = true;
	} catch (KeyNotFoundException &e) {
	}

	return exists;
}

ServiceInterface* SignUpServiceCreator::create(Database& userDb,
		Database& chatDb) {
	return new SignUpService(userDb);
}

string SignUpService::doSignUp(const string& data) const {

	//si no hay error, guardo el usuario en la BD y devuelvo OK
	Json::Value jsonData;
	Json::Reader reader;
	reader.parse(data, jsonData);

	string username = jsonData[SERVICE_USERNAME].asString();
	string password = jsonData[SERVICE_PASSWORD].asString();
	bool exists = checkUsernameExists(username);

	Json::Value output;

	if (!exists) {
		Logger::getLogger()->write(Logger::DEBUG, "Registering new user...");

		User newUser(username, password);

		newUser.modifyStatus(jsonData[SERVICE_USERCONFIG_STATUS].asString());
		newUser.modifyLocation(
				LocationManager::getInstance()->getLocation(
						jsonData[SERVICE_USERCONFIG_LOCATION].asString()));
		newUser.modifyProfilePicture(
				jsonData[SERVICE_USERCONFIG_PICTURE].asString());

		std::vector<std::string> key;
		key.push_back(username);
		this->userDb.write(key, newUser.serialize());

		//le envio sus datos al user como confirmacion
		output[SERVICE_USERCONFIG_LOCATION] = newUser.getLocation();
		output[SERVICE_OUT_OK] = true;
		output[SERVICE_OUT_WHAT] = "";
		Logger::getLogger()->write(Logger::DEBUG,
				"user " + username + " successfully registered.");
	} else {
		output[SERVICE_OUT_OK] = false;
		output[SERVICE_OUT_WHAT] = SERVICE_OUT_USERNAMEEXISTS;
		Logger::getLogger()->write(Logger::DEBUG,
				"Couldn't register user " + username);
	}

	ConnectionManager::getInstance()->updateUser(this->userDb, username);
	return output.toStyledString();
}
