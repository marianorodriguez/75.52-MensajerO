#include <services/CurrentChatsService.h>

const std::string CurrentChatsService::serviceName = SERVICE_CURRENTCHATS_NAME;

std::string CurrentChatsService::getUri() const {
	return CurrentChatsService::serviceName;
}

void CurrentChatsService::executeRequest(const Connection& connection) const {

	Json::Value data;
	data[SERVICE_USERNAME] = connection.getParamMap()[SERVICE_USERNAME];
	data[SERVICE_PASSWORD] = connection.getParamMap()[SERVICE_PASSWORD];

	Json::Value output = doCurrentChats(data);

	connection.printMessage(output.toStyledString());
}

Json::Value CurrentChatsService::doCurrentChats(const Json::Value &data) {

	Database dbUsers(DATABASE_USERS_PATH);
	Database dbChats(DATABASE_CHATS_PATH);

	vector<string> keyUser;
	keyUser.push_back(data[SERVICE_USERNAME].asString());

	Json::Value output;

	try {
		User user(dbUsers.read(keyUser));
		if (user.getPassword() == data[SERVICE_PASSWORD].asString()) {

			vector<string> chats = user.getChats();
			output[SERVICE_CURRENTCHATS_CHATS] = Json::Value(Json::arrayValue);

			for (unsigned int i = 0; i < chats.size(); i++) {
				vector<string> keyChats;
				keyChats.push_back(data[SERVICE_USERNAME].asString());
				keyChats.push_back(chats[i]);
				Chat chat(dbChats.read(keyChats));
				output[SERVICE_CURRENTCHATS_CHATS].append(chat.serialize());
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

ServiceInterface* CurrentChatsServiceCreator::create() {
	return new CurrentChatsService();
}