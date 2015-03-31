#include "Message.h"
#include "../config.h"

Message::Message(string toDeserialize) {

	Json::Value parsedFromString;
	Json::Reader reader;
	reader.parse(toDeserialize, parsedFromString);

	this->userFromID = (parsedFromString["message"]["fromID"]).asString();
	this->userToID = (parsedFromString["message"]["toID"]).asString();
	this->date_time = (parsedFromString["message"]["date_time"]).asString();
	this->message = (parsedFromString["message"]["text"]).asString();
}

Message::Message(string date_time, string from, string to, string message) {

	this->userFromID = from;
	this->userToID = to;
	this->message = message;
	this->date_time = date_time;
}

Message::~Message() {
}

string Message::serialize() {

	Json::Value message;
	message["message"]["fromID"] = this->userFromID;
	message["message"]["toID"] = this->userToID;
	message["message"]["date_time"] = this->date_time;
	message["message"]["text"] = this->message;

	return message.toStyledString();
}
