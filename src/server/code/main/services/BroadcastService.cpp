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

BroadcastService::BroadcastService(Database& userDb) :userDb(userDb) {}

BroadcastService::~BroadcastService() {}

std::string BroadcastService::getUri() const {
	return serviceName;
}

std::string BroadcastService::executeRequest(
		const Json::Value &paramMap) const {

	Json::Reader reader;
	Json::Value data;
	reader.parse(paramMap.asString(), data);
	Logger::getLogger()->write(Logger::INFO, "Executing Broadcast service...");
	Json::Value output = doBroadcast(data);

	ConnectionManager::getInstance()->updateUser(
			data[SERVICE_USERNAME].asString());

	return output.toStyledString();
}

Json::Value BroadcastService::doBroadcast(const Json::Value &data) const {

	Json::Value input;
	input[SERVICE_USERNAME] = data[SERVICE_USERNAME].asString();
	input[SERVICE_PASSWORD] = data[SERVICE_PASSWORD].asString();
	input[SERVICE_SENDMESSAGE_MESSAGE] =
			data[SERVICE_SENDMESSAGE_MESSAGE].asString();

	Json::Value broadcastOut;
	broadcastOut[SERVICE_OUT_OK] = true;
	broadcastOut[SERVICE_OUT_WHAT] = "";

	std::vector<std::string> keyUser;
	keyUser.push_back(data[SERVICE_USERNAME].asString());

	try {
		std::vector<std::string> users = this->userDb.getAllKeys();
		User user(this->userDb.read(keyUser));

		if(user.getPassword() != data[SERVICE_PASSWORD].asString()){
			broadcastOut[SERVICE_OUT_OK] = false;
			broadcastOut[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDPWD;
			Logger::getLogger()->write(Logger::WARN, "Invalid password from user " + user.getUsername());
			return broadcastOut;
		}

		SendMessageService sendMessageService;
		for (unsigned int i = 0; i < users.size(); i++) {
			if (users.at(i) != data[SERVICE_USERNAME].asString()) {
				input[SERVICE_SENDMESSAGE_USERNAME_TO] = users.at(i);
				Logger::getLogger()->write(Logger::DEBUG, "Sending broadcast message to user " + users.at(i));
				Json::Value output = sendMessageService.doSendMessage(input);
				if (output[SERVICE_OUT_WHAT] == SERVICE_OUT_INVALIDUSER) {
					broadcastOut[SERVICE_OUT_OK] = false;
					broadcastOut[SERVICE_OUT_WHAT] = SERVICE_OUT_BROADCASTFAILEDTOSOME;
					Logger::getLogger()->write(Logger::WARN, "Failed to send broadcast message to " + users.at(i));
				}
			}
		}

	} catch (KeyNotFoundException &e) {
		broadcastOut[SERVICE_OUT_OK] = false;
		broadcastOut[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDUSER;
		Logger::getLogger()->write(Logger::WARN, "Some unregistered user tried to use this service.");
	}
	return broadcastOut;
}


ServiceInterface* BroadcastServiceCreator::create(Database& userDb, Database& chatDb) {
	return new BroadcastService(userDb);
}
