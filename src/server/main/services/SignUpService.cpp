#include <services/SignUpService.h>

const std::string SignUpService::serviceName = SERVICE_SIGNUP_NAME;

std::string SignUpService::getUri() const {
	return SignUpService::serviceName;
}

void SignUpService::executeRequest(const Connection& connection) const {

	std::string username = connection.getParamMap()[SERVICE_USERNAME];
	std::string password = connection.getParamMap()[SERVICE_PASSWORD];
	bool error = false;

	checkusernameExists(username, connection, error);

	//si no hay error, guardo el usuario en la BD y devuelvo OK
	if (!error) {
		Database* DB = new Database();
		User* newUser = new User(username, password);

		std::vector<std::string> key;
		key.push_back(username);
		DB->write(key, newUser->serialize());

		//le envio sus datos al user como confirmacion
		connection.printMessage(newUser->serialize());

		delete DB;
		delete newUser;
	}
}

void SignUpService::checkusernameExists(const std::string& username,
		const Connection& connection, bool& found) const {

	Database * DB = new Database();
	vector<string> key;
	key.push_back(username);

	try {
		std::string value = DB->read(key);
		found = true;
	} catch (KeyNotFoundException *e) {	}

	if (found) {
		connection.printMessage("Error: Username already exists.");
		//todo setear connection status
	}

	delete DB;
}
