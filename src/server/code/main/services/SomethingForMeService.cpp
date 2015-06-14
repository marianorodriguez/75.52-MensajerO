#include <../../../include/main/services/SomethingForMeService.h>

const std::string SomethingForMeService::serviceName =
		SERVICE_SOMETHINGFORME_NAME;

std::string SomethingForMeService::getUri() const {
	return SomethingForMeService::serviceName;
}

std::string SomethingForMeService::executeRequest(
		const Json::Value &paramMap) const {

	Json::Reader reader;
	Json::Value data;
	reader.parse(paramMap.asString(), data);
	Json::Value output = doSomethingForMe(data);

	ConnectionManager::getInstance()->updateUser(
			data[SERVICE_USERNAME].asString());

	return output.toStyledString();
}

Json::Value SomethingForMeService::doSomethingForMe(const Json::Value &data) {

	Database dbUsers(DATABASE_USERS_PATH);
	Database dbChats(DATABASE_CHATS_PATH);

	vector<string> keyUser;
	keyUser.push_back(data[SERVICE_USERNAME].asString());

	Json::Value output;

	try {
		User user(dbUsers.read(keyUser));

		if (user.getPassword() == data[SERVICE_PASSWORD].asString()) {

			vector<string> chatsUser = user.getChats();

			for (unsigned int i = 0; i < chatsUser.size(); i++) {

				vector<string> keyChats;
				keyChats.push_back(data[SERVICE_USERNAME].asString());
				keyChats.push_back(chatsUser[i]);
				Chat chat(dbChats.read(keyChats));

				vector<Message> messages = chat.getMessages();
				int cont = 0;

				unsigned int start = 0;
				if (data[SERVICE_USERNAME].asString() == chat.getUsername1()) {
					start = chat.getFirstMessageUser1();
				} else {
					start = chat.getFirstMessageUser2();
				}

				for (unsigned int j = start; j < messages.size(); j++) {

					if ((!messages.at(j).getSent())
							&& (messages.at(j).getUserTo()
									== data[SERVICE_USERNAME].asString())) {

						messages.at(j).setAsSent();
						output[SERVICE_SOMETHINGFORME_MESSAGES][cont] =
								messages.at(j).serialize();
						cont++;
					}
				}
				if (cont != 0) {
					chat.updateMessages(messages);
					dbChats.write(keyChats, chat.serialize());
				}
			}

			output[SERVICE_OUT_OK] = true;
			output[SERVICE_OUT_WHAT] = "";

		} else {
			output[SERVICE_OUT_OK] = false;
			output[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDPWD;
		}
	} catch (KeyNotFoundException& e) {
		output[SERVICE_OUT_OK] = false;
		output[SERVICE_OUT_WHAT] = SERVICE_OUT_INVALIDUSER;
	}

	dbChats.close();
	dbUsers.close();
	return output;
}

ServiceInterface* SomethingForMeServiceCreator::create() {
	return new SomethingForMeService();
}
