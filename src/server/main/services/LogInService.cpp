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
