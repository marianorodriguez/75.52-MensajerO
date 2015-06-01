#include "../../../include/main/services/SignUpService.h"

const std::string SignUpService::serviceName = SERVICE_SIGNUP_NAME;

std::string SignUpService::getUri() const {
	return SignUpService::serviceName;
}

std::string SignUpService::executeRequest(
		const std::map<std::string, std::string> &paramMap) const {

	Json::Value data;
	data[SERVICE_USERNAME] = paramMap.at(SERVICE_USERNAME);
	data[SERVICE_PASSWORD] = paramMap.at(SERVICE_PASSWORD);
	data[SERVICE_USERCONFIG_STATUS] = paramMap.at(SERVICE_USERCONFIG_STATUS);
	data[SERVICE_USERCONFIG_PICTURE] = paramMap.at(SERVICE_USERCONFIG_PICTURE);
	data[SERVICE_USERCONFIG_LOCATION] = paramMap.at(
			SERVICE_USERCONFIG_LOCATION);

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
	} else {
		output[SERVICE_OUT_OK] = false;
		output[SERVICE_OUT_WHAT] = SERVICE_OUT_USERNAMEEXISTS;
	}

	return output;
}

