#include <services/UsersService.h>

const std::string UsersService::serviceName = SERVICE_USERS_NAME;

std::string UsersService::getUri() const {
	return UsersService::serviceName;
}

void UsersService::executeRequest(const Connection& connection) const {

	std::string username = connection.getParamMap()[SERVICE_USERNAME];
	std::string password = connection.getParamMap()[SERVICE_PASSWORD];

	std::vector<std::string> key;
	key.push_back(username);
	Database DB(DATABASE_USERS_PATH);
	std::string userValue = DB.read(key);

	Json::Value jsonUser(userValue);
	std::string userPWD = jsonUser[JSON_USER_ROOT][JSON_USER_PWD].asString();

	if (password == userPWD) {

		Json::Value registeredUsers;
		vector<string> keys = DB.getAllKeys();
		vector<string> key;

		for (int i = 0; i < keys.size(); i++) {
			key.push_back(keys.at(i));
			registeredUsers["users"][keys.at(i)] = DB.read(key);
			key.clear();
		}

		connection.printMessage(registeredUsers.toStyledString());

	} else {

		connection.printMessage("ERROR");
	}
}

ServiceInterface* UsersServiceCreator::create() {
	return new UsersService();
}
