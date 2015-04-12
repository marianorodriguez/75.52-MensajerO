#include "CreateUserService.h"

const std::string CreateUserService::serviceName = "createUser";

const std::string validCharacters = "abcdefghijklmnñopqrstuvwxyz0123456789.-_";

std::string CreateUserService::getUri() const {
	return CreateUserService::serviceName;
}

void CreateUserService::executeRequest(const Connection& connection) const {

	//todo setear estos parametros
	std::string username;
	std::string password;
	bool error = false;

	checkValidUsername(username, connection, error);
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

void CreateUserService::checkValidUsername(const std::string& username,
		const Connection& connection, bool& error) const {

	for (unsigned int i = 0; i < username.size(); i++) {
		if (std::string::npos == validCharacters.find(username[i])) {
			//si no encuentro una letra del username dentro de los validCharacters, error
			error = true;
			break;
		}
	}

	if (error) {
		connection.printMessage("Error: Invalid Username.");
	}
}

void CreateUserService::checkusernameExists(const std::string& username,
		const Connection& connection, bool& error) const {

	Database * DB = new Database();
	vector<string> key;
	key.push_back(username);

	try {
		DB->read(key);
	} catch (KeyNotFoundException &e) {
		error = true;
	}

	if (error) {
		connection.printMessage("Error: Username already exists.");
	}

	delete DB;
}
