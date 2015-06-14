/*
 * BroadcastService.cpp
 *
 *  Created on: 6/6/2015
 *      Author: marian
 */

#include "../../include/main/services/BroadcastService.h"

const std::string BroadcastService::serviceName = SERVICE_BROADCAST_NAME;

std::string BroadcastService::getUri() const {
	return BroadcastService::serviceName;
}

std::string BroadcastService::executeRequest(
		const Json::Value &paramMap) const {

	Json::Reader reader;
	Json::Value data;
	reader.parse(paramMap.asString(), data);
	Json::Value output = doBroadcast(data);

	ConnectionManager::getInstance()->updateUser(
			data[SERVICE_USERNAME].asString());

	return output.toStyledString();
}

Json::Value BroadcastService::doBroadcast(const Json::Value &data) {

	string userFrom = data[SERVICE_USERNAME].asString();
	string password = data[SERVICE_PASSWORD].asString();
	string text = data[SERVICE_SENDMESSAGE_MESSAGE].asString();

	Json::Value output;

	Database dbChats(DATABASE_CHATS_PATH);
	Database dbUsers(DATABASE_USERS_PATH);

	vector<string> users = dbUsers.getAllKeys();

	vector<string> keyUser, keyChat;
	keyUser.push_back(userFrom);

	try {
		User user(dbUsers.read(keyUser));

		if (user.getPassword() == password) {

			for (unsigned int i = 0; i < users.size(); i++) {
				keyUser.clear();
				keyUser.push_back(users.at(i));
				User userToSendMessage = dbUsers.read(keyUser);
				if (userToSendMessage.getUsername() != userFrom
						&& userToSendMessage.isConnected()) {

					string userTo = userToSendMessage.getUsername();
					keyChat.clear();
					keyChat.push_back(userFrom);
					keyChat.push_back(userTo);
					Message message(userFrom, userTo, text);

					try {
						string serializedChat = dbChats.read(keyChat);
						Chat chat(serializedChat);
						chat.addNewMessage(message);
						dbChats.write(keyChat, chat.serialize());
					} catch (KeyNotFoundException &e) {
						Chat chat(userFrom, userTo);
						chat.addNewMessage(message);
						dbChats.write(keyChat, chat.serialize());

						vector<string> keyUserFrom;
						keyUserFrom.push_back(userFrom);
						User userF(dbUsers.read(keyUserFrom));
						userF.addChatWithUser(userTo);

						vector<string> keyUserTo;
						keyUserTo.push_back(userTo);
						User userT(dbUsers.read(keyUserTo));
						userT.addChatWithUser(userFrom);

						dbUsers.write(keyUserFrom, userF.serialize());
						dbUsers.write(keyUserTo, userT.serialize());

					}
				}
				output[SERVICE_OUT_OK] = true;
				output[SERVICE_OUT_WHAT] = "";
			}
		} else {
			output[SERVICE_OUT_OK] = false;
			output[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDPWD;
		}
	} catch (KeyNotFoundException &e) {
		output[SERVICE_OUT_OK] = false;
		output[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDUSER;
	}

	dbChats.close();
	dbUsers.close();
	return output;
}

ServiceInterface* BroadcastServiceCreator::create() {
	return new BroadcastService();
}

