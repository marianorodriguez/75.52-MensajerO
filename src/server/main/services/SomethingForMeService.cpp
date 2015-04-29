#include <services/SomethingForMeService.h>

const std::string SomethingForMeService::serviceName = SERVICE_SOMETHINGFORME_NAME;

std::string SomethingForMeService::getUri() const {
	return SomethingForMeService::serviceName;
}

void SomethingForMeService::executeRequest(const Connection& connection) const {

	string username = connection.getParamMap()[SERVICE_USERNAME];
	string password = connection.getParamMap()[SERVICE_PASSWORD];

	Database dbUsers(DATABASE_USERS_PATH);
	Database dbChats(DATABASE_CHATS_PATH);

	vector<string> keyUser;
	keyUser.push_back(username);

	try {
		User user(dbUsers.read(keyUser));
		if (user.getPassword() != password) {
			connection.printMessage("Error: Contraseña incorrecta");
			return;
		}
		vector<string> chatsUser = user.getChats();

		Json::Value jsonMessages;
		for (unsigned int i = 0; i < chatsUser.size(); i++) {
			vector<string> keyChats;
			keyChats.push_back(username);
			keyChats.push_back(chatsUser[i]);
			Chat chat(dbChats.read(keyChats));
			vector<Message> messages = chat.getMessages();
			int cont = 0;
			for (unsigned int j = 0; j < messages.size(); j++) {
				if ((!messages[i].getSent()) && (messages[i].getUserTo() == username)) {
					messages[i].setAsSent();
					cont++;
					jsonMessages["message" + cont] = messages[i].serialize();
				}
			}
			if (cont != 0) {
				dbChats.write(keyChats,chat.serialize());
			}
		}
		//Devuelvo los mensajes serializados.
		connection.printMessage(jsonMessages.toStyledString());
	} catch (KeyNotFoundException& e) {
		connection.printMessage("Error: Usuario inválido");
	}
}

ServiceInterface* SomethingForMeServiceCreator::create(){
	return new SomethingForMeService();
}
