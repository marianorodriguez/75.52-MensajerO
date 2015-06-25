#include "../../../include/main/services/SomethingForMeService.h"

const std::string SomethingForMeService::serviceName =
		SERVICE_SOMETHINGFORME_NAME;

SomethingForMeService::SomethingForMeService(Database& users, Database& chats) :
		userDb(users), chatDb(chats) {
}

std::string SomethingForMeService::getUri() const {
	return serviceName;
}

std::string SomethingForMeService::executeRequest(
		const string &paramMap) const {

	Logger::getLogger()->write(Logger::INFO,
			"Executing SomethingForMe service...");

	string output = doSomethingForMe(paramMap);

	return output;
}

string SomethingForMeService::doSomethingForMe(
		const string &data) const {

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse(data, jsonData);

	string username = jsonData[SERVICE_USERNAME].asString();
	string password = jsonData[SERVICE_PASSWORD].asString();

	vector<string> keyUser;
	keyUser.push_back(username);

	Json::Value output;

	try {
		User user(userDb.read(keyUser));

		if (user.getPassword() == password) {

			vector<string> chatsUser = user.getChats();
			Logger::getLogger()->write(Logger::DEBUG,
					"Fetching new messages...");
			int cont = 0;
			for (unsigned int i = 0; i < chatsUser.size(); i++) {
				cont = 0;
				vector<string> keyChats;
				keyChats.push_back(username);
				keyChats.push_back(chatsUser[i]);
				Chat chat(chatDb.read(keyChats));

				vector<Message> messages = chat.getMessages();
				int cont = 0;

				unsigned int start = 0;
				if (username == chat.getUsername1()) {
					start = chat.getFirstMessageUser1();
				} else {
					start = chat.getFirstMessageUser2();
				}

				for (unsigned int j = start; j < messages.size(); j++) {

					if ((!messages.at(j).getSent())
							&& (messages.at(j).getUserTo()
									== username)) {

						messages.at(j).setAsSent();
						output[SERVICE_SOMETHINGFORME_MESSAGES][cont] =
								messages.at(j).serialize();
						cont++;
					}
				}
				if (cont != 0) {
					chat.updateMessages(messages);
					chatDb.write(keyChats, chat.serialize());
				}
			}
			ostringstream convert;
			convert << cont;
			Logger::getLogger()->write(Logger::DEBUG,
					"found " + convert.str() + " new messages.");
			output[SERVICE_OUT_OK] = true;
			output[SERVICE_OUT_WHAT] = "";

		} else {
			output[SERVICE_OUT_OK] = false;
			output[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDPWD;
			Logger::getLogger()->write(Logger::WARN,
					"Invalid password from user " + username);
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

ServiceInterface* SomethingForMeServiceCreator::create(Database& userDb,
		Database& chatDb) {
	return new SomethingForMeService(userDb, chatDb);
}
