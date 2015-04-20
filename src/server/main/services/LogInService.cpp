#include <services/LogInService.h>
const std::string LogInService::serviceName = SERVICE_LOGIN_NAME;

std::string LogInService::getUri() const {
	return LogInService::serviceName;
}

void LogInService::executeRequest(const Connection& connection) const {

	string username = connection.getParamMap()[SERVICE_LOGIN_USERNAME];
	string password = connection.getParamMap()[SERVICE_LOGIN_PASSWORD];

	Database* db = new Database(DATABASE_USERS_PATH);
	vector<string> key;
	key.push_back(username);

	try {
		string serializedUser = db->read(key);
		User* user = new User(serializedUser);
		if (user->getPassword() == password) {
			//Devuelvo datos al user.
			connection.printMessage(serializedUser);
			delete db;
			return;
		}
	} catch (KeyNotFoundException &e) {}

	// Si llega aca es porque la password no coincidio o no encontro el username.
	connection.printMessage("ERROR");
	delete db;
}
