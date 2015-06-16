/*
 * Chat.cpp
 *
 *  Created on: 2/4/2015
 *      Author: marian
 */

#include "../../../include/main/user/chat/Chat.h"

Chat::Chat(const string& serializedChat) {

	Json::Value parsedFromString;
	Json::Reader reader;
	bool wasParsed = reader.parse(serializedChat, parsedFromString);

	if (not wasParsed) {
		NotSerializedDataException exception(
				"'" + serializedChat + "' is not a JSON serialized chat.");
		throw exception;
	}

	this->username_1 = parsedFromString[JSON_CHAT_USER_1].asString();
	this->username_2 = parsedFromString[JSON_CHAT_USER_2].asString();

	this->firstMessageUser1 = parsedFromString[JSON_CHAT_FIRST_1].asInt();
	this->firstMessageUser2 = parsedFromString[JSON_CHAT_FIRST_2].asInt();

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
		InvalidUsernameException exception(
				"Can't create a new chat between a single user");
		throw exception;
	}

	this->firstMessageUser1 = 0;
	this->firstMessageUser2 = 0;
	this->username_1 = user_1;
	this->username_2 = user_2;
}

void Chat::addNewMessage(const Message& message) {

	if (isAValidMessage(message)) {

		this->sentMessages.push_back(message);

	} else {
		InvalidUsernameException exception(
				"Can't add a message between invalid users");
		throw exception;
	}

}

vector<Message> Chat::getMessages() const {
	return this->sentMessages;
}

void Chat::updateMessages(const vector<Message> msgs) {

	this->sentMessages = msgs;
}

void Chat::setFirstMessageUser1(const int i) {
	this->firstMessageUser1 = i;
}

void Chat::setFirstMessageUser2(const int i) {
	this->firstMessageUser2 = i;
}

int Chat::getFirstMessageUser1() {
	return this->firstMessageUser1;
}

int Chat::getFirstMessageUser2() {
	return this->firstMessageUser2;
}

string Chat::getUsername1() {
	return this->username_1;
}

string Chat::serialize() const {

	Json::Value JsonChat;
	JsonChat[JSON_CHAT_USER_1] = this->username_1;
	JsonChat[JSON_CHAT_USER_2] = this->username_2;
	JsonChat[JSON_CHAT_FIRST_1] = this->firstMessageUser1;
	JsonChat[JSON_CHAT_FIRST_2] = this->firstMessageUser2;

	for (unsigned int i = 0; i < this->sentMessages.size(); i++) {
		JsonChat[JSON_CHAT_MESSAGES][i] = this->sentMessages.at(i).serialize();
	}

	return JsonChat.toStyledString();
}

string Chat::serializeCurrentChats(const string &user) const {

	Json::Value JsonChat;
	JsonChat[JSON_CHAT_USER_1] = this->username_1;
	JsonChat[JSON_CHAT_USER_2] = this->username_2;
	JsonChat[JSON_CHAT_FIRST_1] = this->firstMessageUser1;
	JsonChat[JSON_CHAT_FIRST_2] = this->firstMessageUser2;

	unsigned int start;
	if (user == this->username_1) {
		start = firstMessageUser1;
	} else {
		start = firstMessageUser2;
	}

	for (unsigned int i = start; i < this->sentMessages.size(); i++) {
		JsonChat[JSON_CHAT_MESSAGES][i-start] = this->sentMessages.at(i).serialize();
	}

	return JsonChat.toStyledString();
}

Chat::~Chat() {
}

bool Chat::isAValidMessage(const Message& m) const {

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

