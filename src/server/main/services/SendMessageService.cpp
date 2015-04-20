#include <services/SendMessageService.h>

const std::string SendMessageService::serviceName = SERVICE_SENDMESSAGE_NAME;

std::string SendMessageService::getUri() const {
	return SendMessageService::serviceName;
}

void SendMessageService::executeRequest(const Connection& connection) const {

	map<string,string> params = connection.getParamMap();
	string userFrom = params[SERVICE_SENDMESSAGE_USERNAME_FROM];
	string userTo = params[SERVICE_SENDMESSAGE_USERNAME_TO];
	string sentMessage = params[SERVICE_SENDMESSAGE_MESSAGE];

	Message* message = new Message(userFrom,userTo,sentMessage);

	Database* dbChats = new Database(DATABASE_CHATS_PATH);
	vector<string> keyChat;
	keyChat.push_back(userFrom);
	keyChat.push_back(userTo);

	try {
		string serializedChat = dbChats->read(keyChat);
		Chat chat(serializedChat);
		chat.addNewMessage(message);
		dbChats->write(keyChat,chat.serialize());
	} catch (KeyNotFoundException &e) {
		Chat chat(userFrom,userTo);
		chat.addNewMessage(message);
		dbChats->write(keyChat,chat.serialize());

		Database* dbUsers = new Database(DATABASE_USERS_PATH);
		vector<string> keyUserFrom; keyUserFrom.push_back(userFrom);
		User* userF = new User(dbUsers->read(keyUserFrom));
		userF->addChatWithUser(userTo);

		vector<string> keyUserTo; keyUserTo.push_back(userTo);
		User* userT = new User(dbUsers->read(keyUserTo));
		userT->addChatWithUser(userFrom);

		dbUsers->write(keyUserFrom,userF->serialize());
		dbUsers->write(keyUserTo,userT->serialize());

		delete userF;
		delete userT;
		delete dbUsers;
	}

	delete message;
	delete dbChats;
}
