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
			parsedFromString[JSON_CHAT_ROOT][JSON_CHAT_USER_1].asString();
	this->username_2 =
			parsedFromString[JSON_CHAT_ROOT][JSON_CHAT_USER_2].asString();
	this->numberOfMessages = 0;

	int num_msg = parsedFromString[JSON_CHAT_ROOT][JSON_CHAT_NUM_MSG].asInt();
	for (int i = 0; i < num_msg; i++) {

		string serializedMessage =
				parsedFromString[JSON_CHAT_ROOT][JSON_CHAT_MESSAGES][i].asString();
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
	this->numberOfMessages = 0;
}

void Chat::addNewMessage(const Message& message) {

	if (isAValidMessage(message)) {

		this->sentMessages.push_back(message);
		this->numberOfMessages++;

	} else {
		InvalidUsernameException exception("Can't add a message between invalid users");
		throw exception;
	}

}

string Chat::serialize() const{

	Json::Value JsonChat;
	JsonChat[JSON_CHAT_ROOT][JSON_CHAT_USER_1] = this->username_1;
	JsonChat[JSON_CHAT_ROOT][JSON_CHAT_USER_2] = this->username_2;
	JsonChat[JSON_CHAT_ROOT][JSON_CHAT_NUM_MSG] = this->numberOfMessages;

	for (int i = 0; i < this->numberOfMessages; i++) {
		JsonChat[JSON_CHAT_ROOT][JSON_CHAT_MESSAGES][i] = this->sentMessages.at(
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

