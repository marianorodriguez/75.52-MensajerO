/*
 * Chat.cpp
 *
 *  Created on: 2/4/2015
 *      Author: marian
 */

#include "Chat.h"

Chat::Chat(const string& serializedChat) {

	Json::Value parsedFromString;
	Json::Reader reader;
	bool wasParsed = reader.parse(serializedChat, parsedFromString);

	if (not wasParsed) {
		NotSerializedDataException exception("'" + serializedChat +
							"' is not a JSON serialized chat.");
		throw exception;
	}

	this->username_1 =
			parsedFromString[JSON_CHAT_USER_1].asString();
	this->username_2 =
			parsedFromString[JSON_CHAT_USER_2].asString();

	int num_msg = parsedFromString[JSON_CHAT_MESSAGES].size();
	for (int i = 0; i < num_msg; i++) {

		string serializedMessage =
				parsedFromString[JSON_CHAT_MESSAGES][i].asString();
		Message message(serializedMessage);
		this->addNewMessage(message);

	}
}

Chat::Chat(const string& user_1, const string& user_2) {

	if (user_1 == user_2) {
		InvalidUsernameException exception("Can't create a new chat between a single user");
		throw exception;
	}

	this->username_1 = user_1;
	this->username_2 = user_2;
}

void Chat::addNewMessage(const Message& message) {

	if (isAValidMessage(message)) {

		this->sentMessages.push_back(message);

	} else {
		InvalidUsernameException exception("Can't add a message between invalid users");
		throw exception;
	}

}

vector<Message> Chat::getMessages() const {
	return this->sentMessages;
}

void Chat::updateMessages(const vector<Message> msgs){

	this->sentMessages = msgs;
}

string Chat::serialize() const{

	Json::Value JsonChat;
	JsonChat[JSON_CHAT_USER_1] = this->username_1;
	JsonChat[JSON_CHAT_USER_2] = this->username_2;

	for (unsigned int i = 0; i < this->sentMessages.size(); i++) {
		JsonChat[JSON_CHAT_MESSAGES][i] = this->sentMessages.at(
				i).serialize();
	}

	return JsonChat.toStyledString();
}

Chat::~Chat() {
}

bool Chat::isAValidMessage(const Message& m) const{

	string from = m.getUserFrom();
	string to = m.getUserTo();
	bool valid = false;

	if (((from == this->username_1) || (from == this->username_2))
			&& ((to == this->username_1) || (to == this->username_2))) {

		if (from != to)
			valid = true;
	}

	return valid;
}

