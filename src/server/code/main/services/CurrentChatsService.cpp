#include <../../include/main/services/CurrentChatsService.h>
#include "json.h"

const std::string CurrentChatsService::serviceName = SERVICE_CURRENTCHATS_NAME;

CurrentChatsService::CurrentChatsService(Database& userDb, Database& chatDb) :
	userDb(userDb), chatDb(chatDb){}

CurrentChatsService::~CurrentChatsService(){}


std::string CurrentChatsService::getUri() const {
	return CurrentChatsService::serviceName;
}

std::string CurrentChatsService::executeRequest(
		const Json::Value &paramMap) const {

	Json::Reader reader;
	Json::Value data;
	reader.parse(paramMap.asString(), data);
	Json::Value output = doCurrentChats(data);

	ConnectionManager::getInstance()->updateUser(
			data[SERVICE_USERNAME].asString());

	return output.toStyledString();
}

Json::Value CurrentChatsService::doCurrentChats(const Json::Value &data) const {

	vector<string> keyUser;
	keyUser.push_back(data[SERVICE_USERNAME].asString());

	Json::Value output;

	try {
		User user(this->userDb.read(keyUser));
		if (user.getPassword() == data[SERVICE_PASSWORD].asString()) {

			vector<string> chats = user.getChats();
			std::string username = data[SERVICE_USERNAME].asString();
			output[SERVICE_CURRENTCHATS_CHATS] = serializeUserChats(username, chats);

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

Json::Value CurrentChatsService::serializeUserChats(const std::string& username,
										const std::vector<std::string>& chats) const{
	Json::Value jsonArray(Json::arrayValue) ;
	for (unsigned int i = 0; i < chats.size(); i++) {
		std::vector<std::string> keyChats;
		keyChats.push_back(username);
		keyChats.push_back(chats[i]);
		Chat chat(this->chatDb.read(keyChats));
		jsonArray.append(chat.serializeCurrentChats(username));
	}
	return jsonArray;
}

ServiceInterface* CurrentChatsServiceCreator::create(Database& userDb, Database& chatDb) {
	return new CurrentChatsService(userDb, chatDb);
}
