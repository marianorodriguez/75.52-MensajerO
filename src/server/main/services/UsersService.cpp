#include <services/UsersService.h>

const std::string UsersService::serviceName = SERVICE_USERS_NAME;

std::string UsersService::getUri() const {
	return UsersService::serviceName;
}

void UsersService::executeRequest(const Connection& connection) const {

	Json::Value data;
	data[SERVICE_USERNAME] = connection.getParamMap()[SERVICE_USERNAME];
	data[SERVICE_PASSWORD] = connection.getParamMap()[SERVICE_PASSWORD];
	//TODO procesar location

	Json::Value output = doUsers(data);

	connection.printMessage(output.toStyledString());
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

			vector<string> keys = DB.getAllKeys();
			vector<string> key;

			for (int i = 0; i < keys.size(); i++) {
				key.push_back(keys.at(i));
				output["users"][i] = DB.read(key);
				key.clear();
			}

			output[SERVICE_OUT_OK] = true;
			output[SERVICE_OUT_WHAT] = "";

		} else {
			output[SERVICE_OUT_OK] = false;
			output[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDPWD;
		}
	} catch (KeyNotFoundException &e) {
		output[SERVICE_OUT_OK] = false;
		output[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDUSER;
	}

	return output;
}

ServiceInterface* UsersServiceCreator::create() {
	return new UsersService();
}
