#include "../../include/main/services/SendMessageService.h"

const std::string SendMessageService::serviceName = SERVICE_SENDMESSAGE_NAME;

SendMessageService::SendMessageService(Database& userDb, Database& chatDb) :
										userDb(userDb), chatDb(chatDb){}


SendMessageService::~SendMessageService() {}

std::string SendMessageService::getUri() const {
	return serviceName;
}

std::string SendMessageService::executeRequest(
		const Json::Value &paramMap) const {

	Json::Reader reader;
	Json::Value data;
	reader.parse(paramMap.asString(), data);
	Logger::getLogger()->write(Logger::INFO,
			"Executing SendMessage service...");
	Json::Value output = doSendMessage(data);

	ConnectionManager::getInstance()->updateUser(
			data[SERVICE_USERNAME].asString());

	return output.toStyledString();
}

Json::Value SendMessageService::doSendMessage(const Json::Value &data) const {

	string userFrom = data[SERVICE_USERNAME].asString();
	string password = data[SERVICE_PASSWORD].asString();
	string userTo = data[SERVICE_SENDMESSAGE_USERNAME_TO].asString();
	string text = data[SERVICE_SENDMESSAGE_MESSAGE].asString();

	Message message(userFrom, userTo, text);

	vector<string> keyChat, keyUser;
	keyChat.push_back(userFrom);
	keyChat.push_back(userTo);
	keyUser.push_back(userFrom);

	Json::Value output;

	try {
		User user(userDb.read(keyUser));

		if (user.getPassword() == password) {
			try {
				Logger::getLogger()->write(Logger::DEBUG,
						"Sending message from " + user.getUsername() + " to "
								+ userTo);
				string serializedChat = chatDb.read(keyChat);
				Chat chat(serializedChat);
				chat.addNewMessage(message);
				chatDb.write(keyChat, chat.serialize());
			} catch (KeyNotFoundException &e) {
				Logger::getLogger()->write(Logger::DEBUG,
						"Chat not found, starting new conversation.");
				Chat chat(userFrom, userTo);
				chat.addNewMessage(message);
				chatDb.write(keyChat, chat.serialize());

				vector<string> keyUserFrom;
				keyUserFrom.push_back(userFrom);
				User userF(userDb.read(keyUserFrom));
				userF.addChatWithUser(userTo);

				vector<string> keyUserTo;
				keyUserTo.push_back(userTo);
				User userT(userDb.read(keyUserTo));
				userT.addChatWithUser(userFrom);

				userDb.write(keyUserFrom, userF.serialize());
				userDb.write(keyUserTo, userT.serialize());

			}
			output[SERVICE_OUT_OK] = true;
			output[SERVICE_OUT_WHAT] = "";
		} else {
			output[SERVICE_OUT_OK] = false;
			output[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDPWD;
			Logger::getLogger()->write(Logger::WARN,
					"Invalid password from user " + user.getUsername());
		}
	} catch (KeyNotFoundException& e) {
		output[SERVICE_OUT_OK] = false;
		output[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDUSER;
		Logger::getLogger()->write(Logger::WARN,
				"Some unregistered user tried to use this service.");
	}
	return output;
}

ServiceInterface* SendMessageServiceCreator::create(Database& userDb, Database& chatDb) {
	return new SendMessageService(userDb, chatDb);
}

