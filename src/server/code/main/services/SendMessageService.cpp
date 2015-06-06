#include <../../include/main/services/SendMessageService.h>

const std::string SendMessageService::serviceName = SERVICE_SENDMESSAGE_NAME;

std::string SendMessageService::getUri() const {
	return SendMessageService::serviceName;
}

std::string SendMessageService::executeRequest(
		const Json::Value &paramMap) const {

	Json::Reader reader;
	Json::Value data;
	reader.parse(paramMap.asString(), data);
	Json::Value output = doSendMessage(data);

	ConnectionManager::getInstance()->updateUser(
			data[SERVICE_USERNAME].asString());

	return output.toStyledString();
}

Json::Value SendMessageService::doSendMessage(const Json::Value &data) {

	string userFrom = data[SERVICE_USERNAME].asString();
	string password = data[SERVICE_PASSWORD].asString();
	string userTo = data[SERVICE_SENDMESSAGE_USERNAME_TO].asString();
	string text = data[SERVICE_SENDMESSAGE_MESSAGE].asString();

	Message message(userFrom, userTo, text);

	Database dbChats(DATABASE_CHATS_PATH);
	Database dbUsers(DATABASE_USERS_PATH);
	vector<string> keyChat, keyUser;
	keyChat.push_back(userFrom);
	keyChat.push_back(userTo);
	keyUser.push_back(userFrom);

	Json::Value output;

	try {
		User user(dbUsers.read(keyUser));

		if (user.getPassword() == password) {
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

ServiceInterface* SendMessageServiceCreator::create() {
	return new SendMessageService();
}
