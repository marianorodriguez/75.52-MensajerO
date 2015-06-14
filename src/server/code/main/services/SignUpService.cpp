#include "../../../include/main/services/SignUpService.h"

const std::string SignUpService::serviceName = SERVICE_SIGNUP_NAME;

SignUpService::SignUpService(Database& userDb) : userDb(userDb){}


std::string SignUpService::getUri() const {
	return SignUpService::serviceName;
}

std::string SignUpService::executeRequest(const Json::Value &paramMap) const {

	Json::Reader reader;
	Json::Value data;
	reader.parse(paramMap.asString(), data);
	Json::Value output = doSignUp(data);

	ConnectionManager::getInstance()->updateUser(
			data[SERVICE_USERNAME].asString());

	return output.toStyledString();
}

bool SignUpService::checkUsernameExists(const std::string& username) const{

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

ServiceInterface* SignUpServiceCreator::create(Database& userDb, Database& chatDb) {
	return new SignUpService(userDb);
}

Json::Value SignUpService::doSignUp(const Json::Value& data) const {

	//si no hay error, guardo el usuario en la BD y devuelvo OK

	bool exists = checkUsernameExists(data[SERVICE_USERNAME].asString());

	Json::Value output;

	if (!exists) {
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
		this->userDb.write(key, newUser.serialize());

		//le envio sus datos al user como confirmacion
		output[SERVICE_USERCONFIG_LOCATION] = newUser.getLocation();
		output[SERVICE_OUT_OK] = true;
		output[SERVICE_OUT_WHAT] = "";
	} else {
		output[SERVICE_OUT_OK] = false;
		output[SERVICE_OUT_WHAT] = SERVICE_OUT_USERNAMEEXISTS;
	}

	return output;
}

