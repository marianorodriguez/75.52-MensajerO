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

	Database* db = new Database(DATABASE_CHATS_PATH);
	vector<string> key;
	key.push_back(userFrom);
	key.push_back(userTo);

	try {
		string serializedChat = db->read(key);
		Chat chat(serializedChat);
		chat.addNewMessage(message);
		db->write(key,chat.serialize());
	} catch (KeyNotFoundException &e) {
		Chat chat(userFrom,userTo);
		chat.addNewMessage(message);
		db->write(key,chat.serialize());
	}

	delete message;
	delete db;
}
