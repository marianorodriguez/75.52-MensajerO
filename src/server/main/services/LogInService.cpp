#include "services/LogInService.h"
const std::string LogInService::serviceName = SERVICE_LOGIN_NAME;

std::string LogInService::getUri() const {
	return LogInService::serviceName;
}

void LogInService::executeRequest(const Connection& connection) const {

	Json::Value data;
	data[SERVICE_USERNAME] = connection.getParamMap()[SERVICE_USERNAME];
	data[SERVICE_PASSWORD] = connection.getParamMap()[SERVICE_PASSWORD];
	data["latitude"] = 0;
	data["longitude"] = 0;

	Json::Value output = doLogIn(data);

	connection.printMessage(output.toStyledString());
}

ServiceInterface* LogInServiceCreator::create() {
	return new LogInService();
}

Json::Value LogInService::doLogIn(const Json::Value& data) {

	Database db(DATABASE_USERS_PATH);
	vector<string> key;
	key.push_back(data[SERVICE_USERNAME].asString());

	//TODO FALTA PROCESAR LA LOCATION

	Json::Value output;

	try {
		string serializedUser = db.read(key);
		User user(serializedUser);
		if (user.getPassword() == data[SERVICE_PASSWORD].asString()) {
			output["ok"] = true;
			output["what"] = "";
		} else {
			output["ok"] = false;
			output["what"] = "Error: Invalid password.";
		}

	} catch (KeyNotFoundException &e) {
		output["ok"] = false;
		output["what"] = "Error: Invalid username.";
	}

	return output;
}
