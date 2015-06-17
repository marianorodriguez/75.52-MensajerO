/*
 * DeleteChatService.cpp
 *
 *  Created on: 30/5/2015
 *      Author: marian
 */

#include "../../include/main/services/DeleteChatService.h"

const std::string DeleteChatService::serviceName = SERVICE_DELETECHAT_NAME;

DeleteChatService::DeleteChatService(Database& userDb, Database& chatDb) :
	userDb(userDb), chatDb(chatDb) {}


DeleteChatService::~DeleteChatService() {}


std::string DeleteChatService::getUri() const {
	return DeleteChatService::serviceName;
}

std::string DeleteChatService::executeRequest(
		const Json::Value &paramMap) const {

	Json::Reader reader;
	Json::Value data;
	reader.parse(paramMap.asString(), data);
	Json::Value output = doDeleteChat(data);

	ConnectionManager::getInstance()->updateUser(
			data[SERVICE_USERNAME].asString());

	return output.toStyledString();
}

Json::Value DeleteChatService::doDeleteChat(const Json::Value &data) const {
	std::vector<std::string> key;
	std::string username = data[SERVICE_USERNAME].asString();
	std::string otherUser = data[SERVICE_DELETECHAT_WHO].asString();

	key.push_back(username);

	Json::Value output;

	try {
		std::string serializedUser = this->userDb.read(key);
		User user(serializedUser);
		if (user.getPassword() == data[SERVICE_PASSWORD].asString()) {

			key.push_back(otherUser);

			Chat chat(this->chatDb.read(key));
			int lastMessage = chat.getMessages().size();

			if (username == chat.getUsername1()) {
				chat.setFirstMessageUser1(lastMessage);
			} else {
				chat.setFirstMessageUser2(lastMessage);
			}

			this->chatDb.write(key, chat.serialize());

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

ServiceInterface* DeleteChatServiceCreator::create(Database& userDb, Database& chatDb) {
	return new DeleteChatService(userDb, chatDb);
}
