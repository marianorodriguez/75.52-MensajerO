#include "../../include/main/services/SendMessageService.h"

const std::string SendMessageService::serviceName = SERVICE_SENDMESSAGE_NAME;

SendMessageService::SendMessageService(Database& userDb, Database& chatDb) :
										userDb(userDb), chatDb(chatDb){}


SendMessageService::~SendMessageService() {}

std::string SendMessageService::getUri() const {
	return serviceName;
}

std::string SendMessageService::executeRequest(
		const std::string &paramMap) const {

	Logger::getLogger()->write(Logger::INFO,
			"Executing SendMessage service...");

	string output = doSendMessage(paramMap);

	return output;
}

string SendMessageService::doSendMessage(const string &data) const {

	Json::Value jsonIn;
	Json::Reader reader;
	reader.parse(data, jsonIn);

	string username = jsonIn[SERVICE_USERNAME].asString();
	string password = jsonIn[SERVICE_PASSWORD].asString();
	string userTo = jsonIn[SERVICE_SENDMESSAGE_USERNAME_TO].asString();
	string text = jsonIn[SERVICE_SENDMESSAGE_MESSAGE].asString();

	Message message(username, userTo, text);

	vector<string> keyChat, keyUser;
	keyChat.push_back(username);
	keyChat.push_back(userTo);
	keyUser.push_back(username);

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
				Chat chat(username, userTo);
				chat.addNewMessage(message);
				chatDb.write(keyChat, chat.serialize());

				vector<string> keyUserFrom;
				keyUserFrom.push_back(username);
				User userF(userDb.read(keyUserFrom));
				userF.addChatWithUser(userTo);

				vector<string> keyUserTo;
				keyUserTo.push_back(userTo);
				User userT(userDb.read(keyUserTo));
				userT.addChatWithUser(username);

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

	ConnectionManager::getInstance()->updateUser(userDb, username);
	return output.toStyledString();
}

ServiceInterface* SendMessageServiceCreator::create(Database& userDb, Database& chatDb) {
	return new SendMessageService(userDb, chatDb);
}

