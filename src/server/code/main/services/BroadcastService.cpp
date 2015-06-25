/*
 * BroadcastService.cpp
 *
 *  Created on: 6/6/2015
 *      Author: marian
 */

#include "../../include/main/services/BroadcastService.h"
#include "../../include/main/database/Database.h"
#include "../../include/main/user/chat/Chat.h"
#include "../../include/main/user/User.h"

const std::string serviceName = SERVICE_BROADCAST_NAME;

BroadcastService::BroadcastService(Database& userDb, Database& chatDb) :
		userDb(userDb), chatDb(chatDb) {
}

BroadcastService::~BroadcastService() {
}

std::string BroadcastService::getUri() const {
	return serviceName;
}

std::string BroadcastService::executeRequest(
		const string &paramMap) const {

	Json::StyledWriter writer;
	Logger::getLogger()->write(Logger::INFO, "Executing Broadcast service...");

	string output = doBroadcast(paramMap);

	return output;

}

string BroadcastService::doBroadcast(const string &data) const {

	Json::Value input, jsonIn;
	Json::Reader reader;

	reader.parse(data, jsonIn);

	string username = jsonIn[SERVICE_USERNAME].asString();
	string password = jsonIn[SERVICE_PASSWORD].asString();
	string message = jsonIn[SERVICE_SENDMESSAGE_MESSAGE].asString();

	input[SERVICE_USERNAME] = username;
	input[SERVICE_PASSWORD] = password;
	input[SERVICE_SENDMESSAGE_MESSAGE] = message;

	Json::Value broadcastOut;
	broadcastOut[SERVICE_OUT_OK] = true;
	broadcastOut[SERVICE_OUT_WHAT] = "";

	std::vector<std::string> keyUser;
	keyUser.push_back(username);

	try {
		std::vector<std::string> users = this->userDb.getAllKeys();
		User user(this->userDb.read(keyUser));

		if (user.getPassword() != password) {
			broadcastOut[SERVICE_OUT_OK] = false;
			broadcastOut[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDPWD;
			Logger::getLogger()->write(Logger::WARN,
					"Invalid password from user " + user.getUsername());
			return broadcastOut.toStyledString();
		}

		SendMessageService sendMessageService(this->userDb, this->chatDb);
		for (unsigned int i = 0; i < users.size(); i++) {
			if (users.at(i) != username) {
				input[SERVICE_SENDMESSAGE_USERNAME_TO] = users.at(i);
				Logger::getLogger()->write(Logger::DEBUG,
						"Sending broadcast message to user " + users.at(i));
				string output = sendMessageService.doSendMessage(input.toStyledString());
				Json::Value something4meOut;
				reader.parse(output, something4meOut);
				if (something4meOut[SERVICE_OUT_WHAT] == SERVICE_OUT_INVALIDUSER) {
					broadcastOut[SERVICE_OUT_OK] = false;
					broadcastOut[SERVICE_OUT_WHAT] =
							SERVICE_OUT_BROADCASTFAILEDTOSOME;
					Logger::getLogger()->write(Logger::WARN,
							"Failed to send broadcast message to "
									+ users.at(i));
				}
			}
		}

	} catch (KeyNotFoundException &e) {
		broadcastOut[SERVICE_OUT_OK] = false;
		broadcastOut[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDUSER;
		Logger::getLogger()->write(Logger::WARN,
				"Some unregistered user tried to use this service.");
	}

	ConnectionManager::getInstance()->updateUser(this->userDb, username);

	return broadcastOut.toStyledString();
}

ServiceInterface* BroadcastServiceCreator::create(Database& userDb,
		Database& chatDb) {
	return new BroadcastService(userDb, chatDb);
}
