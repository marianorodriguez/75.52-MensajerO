#include <../../include/main/services/CurrentChatsService.h>

const std::string serviceName = SERVICE_CURRENTCHATS_NAME;

std::string CurrentChatsService::getUri() const {
	return serviceName;
}

std::string CurrentChatsService::executeRequest(
		const Json::Value &paramMap) const {

	Json::Reader reader;
	Json::Value data;
	reader.parse(paramMap.asString(), data);
	Logger::getLogger()->write(Logger::INFO,
			"Executing CurrentChats service...");
	Json::Value output = doCurrentChats(data);

	ConnectionManager::getInstance()->updateUser(
			data[SERVICE_USERNAME].asString());

	return output.toStyledString();
}

Json::Value CurrentChatsService::doCurrentChats(const Json::Value &data) {

	Database dbUsers(DATABASE_USERS_PATH);
	Database dbChats(DATABASE_CHATS_PATH);

	vector<string> keyUser;
	keyUser.push_back(data[SERVICE_USERNAME].asString());

	Json::Value output;

	try {
		User user(dbUsers.read(keyUser));
		if (user.getPassword() == data[SERVICE_PASSWORD].asString()
				&& user.getLoginToken() == data[SERVICE_TOKEN].asDouble()) {

			if (user.isLoggedIn()) {
				vector<string> chats = user.getChats();
				output[SERVICE_CURRENTCHATS_CHATS] = Json::Value(
						Json::arrayValue);
				vector<string> keyChats;
				for (unsigned int i = 0; i < chats.size(); i++) {
					keyChats.clear();
					keyChats.push_back(data[SERVICE_USERNAME].asString());
					keyChats.push_back(chats[i]);
					Logger::getLogger()->write(Logger::DEBUG,
							"Fetching chat between " + user.getUsername()
									+ " and " + chats[i]);
					Chat chat(dbChats.read(keyChats));
					output[SERVICE_CURRENTCHATS_CHATS].append(
							chat.serializeCurrentChats(
									data[SERVICE_USERNAME].asString()));
				}
				output[SERVICE_OUT_OK] = true;
				output[SERVICE_OUT_WHAT] = "";
			} else {
				output[SERVICE_OUT_OK] = false;
				output[SERVICE_OUT_WHAT] = SERVICE_OUT_NOTLOGGEDUSER;
				Logger::getLogger()->write(Logger::WARN,
						"User " + user.getUsername() + " is not logged in.");
			}
		} else {
			output[SERVICE_OUT_OK] = false;
			output[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDPWD;
			Logger::getLogger()->write(Logger::WARN,
					"Invalid password from user " + user.getUsername());
		}
	} catch (KeyNotFoundException &e) {
		output[SERVICE_OUT_OK] = false;
		output[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDUSER;
		Logger::getLogger()->write(Logger::WARN,
				"Some unregistered user tried to use this service.");
	}

	dbChats.close();
	dbUsers.close();
	return output;
}

ServiceInterface* CurrentChatsServiceCreator::create() {
	return new CurrentChatsService();
}
