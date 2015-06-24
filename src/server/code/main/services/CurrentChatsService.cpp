#include "../../include/main/services/CurrentChatsService.h"
#include "json.h"

const std::string CurrentChatsService::serviceName = SERVICE_CURRENTCHATS_NAME;

CurrentChatsService::CurrentChatsService(Database& userDb, Database& chatDb) :
		userDb(userDb), chatDb(chatDb) {
}

CurrentChatsService::~CurrentChatsService() {
}

std::string CurrentChatsService::getUri() const {
	return serviceName;
}

std::string CurrentChatsService::executeRequest(
		const string &paramMap) const {

	Logger::getLogger()->write(Logger::INFO,
			"Executing CurrentChats service...");

	string output = doCurrentChats(paramMap);

	return output;
}

string CurrentChatsService::doCurrentChats(const string &data) const {

	Json::Value jsonIn;
	Json::Reader reader;
	reader.parse(data, jsonIn);
	string username = jsonIn[SERVICE_USERNAME].asString();
	string password = jsonIn[SERVICE_PASSWORD].asString();
	vector<string> keyUser;
	keyUser.push_back(username);

	Json::Value output;

	try {
		User user(this->userDb.read(keyUser));
		if (user.getPassword() == password) {

			vector<string> chats = user.getChats();
			output[SERVICE_CURRENTCHATS_CHATS] = serializeUserChats(username,
					chats);
			output[SERVICE_OUT_OK] = true;
			output[SERVICE_OUT_WHAT] = "";

		} else {
			output[SERVICE_OUT_OK] = false;
			output[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDPWD;
			Logger::getLogger()->write(Logger::WARN,
					"Invalid password from user " + username);
		}
	} catch (KeyNotFoundException &e) {
		output[SERVICE_OUT_OK] = false;
		output[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDUSER;
		Logger::getLogger()->write(Logger::WARN,
				"Some unregistered user tried to use this service.");
	}

	ConnectionManager::getInstance()->updateUser(this->userDb, username);
	return output.toStyledString();
}

Json::Value CurrentChatsService::serializeUserChats(const std::string& username,
		const std::vector<std::string>& chats) const {
	Json::Value jsonArray(Json::arrayValue);
	for (unsigned int i = 0; i < chats.size(); i++) {
		std::vector<std::string> keyChats;
		keyChats.push_back(username);
		keyChats.push_back(chats[i]);
		Logger::getLogger()->write(Logger::DEBUG,
				"Fetching chat between " + username + " and " + chats[i]);
		Chat chat(this->chatDb.read(keyChats));
		jsonArray.append(chat.serializeCurrentChats(username));
	}
	return jsonArray;
}

ServiceInterface* CurrentChatsServiceCreator::create(Database& userDb,
		Database& chatDb) {
	return new CurrentChatsService(userDb, chatDb);
}
