#include <services/CurrentChatsService.h>

const std::string CurrentChatsService::serviceName = SERVICE_CURRENTCHATS_NAME;

std::string CurrentChatsService::getUri() const {
	return CurrentChatsService::serviceName;
}

void CurrentChatsService::executeRequest(const Connection& connection) const {

	std::string username = connection.getParamMap()[SERVICE_USERNAME];
	std::string password = connection.getParamMap()[SERVICE_PASSWORD];

	Database dbUsers(DATABASE_USERS_PATH);
	Database dbChats(DATABASE_CHATS_PATH);

	vector<string> keyUser;
	keyUser.push_back(username);
	try {
		User user(dbUsers.read(keyUser));
		if (user.getPassword() != password){
			connection.printMessage("Error: Contraseña incorrecta");
			return;
		}
		vector<string> chats = user.getChats();
		Json::Value jsonChats;
		for(unsigned int i = 0; i < chats.size(); i++){
			vector<string> keyChats;
			keyChats.push_back(username);
			keyChats.push_back(chats[i]);
			Chat chat(dbChats.read(keyChats));
			jsonChats["chat" + i] = chat.serialize();
		}
		//Devuelvo los mensajes serializados.
		connection.printMessage(jsonChats.toStyledString());
	}catch (KeyNotFoundException &e) {
		connection.printMessage("Error: Usuario inválido");
	}
}

ServiceInterface* CurrentChatsServiceCreator::create(){
	return new CurrentChatsService();
}
