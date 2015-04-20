#include <services/SomethingForMeService.h>

const std::string SomethingForMeService::serviceName = SERVICE_SOMETHINGFORME_NAME;

std::string SomethingForMeService::getUri() const {
	return SomethingForMeService::serviceName;
}

void SomethingForMeService::executeRequest(const Connection& connection) const {

	string username = connection.getParamMap()[SERVICE_LOGIN_USERNAME];

	Database* dbUsers = new Database(DATABASE_USERS_PATH);
	Database* dbChats = new Database(DATABASE_CHATS_PATH);

	vector<string> keyUser;
	keyUser.push_back(username);
	User* user = new User(dbUsers->read(keyUser));
	vector<string> chatsUser = user->getChats();

	Json::Value jsonMessages;
	for (unsigned int i = 0; i < chatsUser.size(); i++) {
		vector<string> keyChats;
		keyChats.push_back(username);
		keyChats.push_back(chatsUser[i]);
		Chat* chat = new Chat(dbChats->read(keyChats));
		vector<Message*> messages = chat->getMessages();
		int cont = 0;
		for (unsigned int j = 0; j < messages.size(); j++) {
			if (!messages[i]->getSent()) {
				messages[i]->setAsSent();
				cont++;
				jsonMessages["message" + cont] = messages[i]->serialize();
			}
		}
		if (cont != 0) {
			dbChats->write(keyChats,chat->serialize());
		}
		delete chat;
	}

	connection.printMessage(jsonMessages.toStyledString());

	delete dbUsers;
	delete dbChats;
	delete user;

}
