#include <services/SignUpService.h>

const std::string SignUpService::serviceName = SERVICE_SIGNUP_NAME;

std::string SignUpService::getUri() const {
	return SignUpService::serviceName;
}

void SignUpService::executeRequest(const Connection& connection) const {

	std::string username = connection.getParamMap()[SERVICE_SIGNUP_USERNAME];
	std::string password = connection.getParamMap()[SERVICE_SIGNUP_PASSWORD];
	bool exists = checkUsernameExists(username, connection);

	//si no hay error, guardo el usuario en la BD y devuelvo OK
	if (!exists) {
		Database DB;
		User newUser(username, password);

		std::vector<std::string> key;
		key.push_back(username);
		DB.write(key, newUser.serialize());

		//le envio sus datos al user como confirmacion
		connection.printMessage(newUser.serialize());
	}
}

bool SignUpService::checkUsernameExists(const std::string& username,
		const Connection& connection) const {
	bool exists = false;
	Database DB;
	vector<string> key;
	key.push_back(username);

	try {
		std::string value = DB.read(key);
		exists = true;
	} catch (KeyNotFoundException *e) {	}

	if (exists) {
		connection.printMessage("Error: Username already exists.");
		//todo setear connection status
	}
	return exists;
}

ServiceInterface* SignUpServiceCreator::create(){
	return new SignUpService();
}