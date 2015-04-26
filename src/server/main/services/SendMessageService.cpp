#include <services/SendMessageService.h>

const std::string SendMessageService::serviceName = "sendMessage";

std::string SendMessageService::getUri() const {
	return SendMessageService::serviceName;
}

void SendMessageService::executeRequest(const Connection& connection) const {

	map<string,string> params = connection.getParamMap();
	string userFrom;	// = params["userFrom"];
	string userTo;		// = params["userTo"];
	string sentMessage;		// = params["message"];

	Message* message = new Message(userFrom,userTo,sentMessage);

	Database* db = new Database(DATABASE_CHAT_PATH);
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

ServiceInterface* SendMessageServiceCreator::create(){
	return new SendMessageService();
}

