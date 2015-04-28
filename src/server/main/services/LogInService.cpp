#include <services/LogInService.h>
const std::string LogInService::serviceName = SERVICE_LOGIN_NAME;

std::string LogInService::getUri() const {
	return LogInService::serviceName;
}

void LogInService::executeRequest(const Connection& connection) const {

	string username = connection.getParamMap()[SERVICE_USERNAME];
	string password = connection.getParamMap()[SERVICE_PASSWORD];

	Database db(DATABASE_USERS_PATH);
	vector<string> key;
	key.push_back(username);

	try {
		string serializedUser = db.read(key);
		User user(serializedUser);
		if (user.getPassword() == password) {
			//Devuelvo datos al user.
			connection.printMessage(serializedUser);
			return;
		} else {
			connection.printMessage("Error: Contraseña incorrecta");
		}

	} catch (KeyNotFoundException &e) {
		connection.printMessage("Error: Usuario incorrecto");
	}
}
