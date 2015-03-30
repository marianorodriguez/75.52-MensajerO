/*
 * Message.cpp
 *
 *  Created on: 29/3/2015
 *      Author: marian
 */

#include "Message.h"
#include "../config.h"
#include "../utilities/stringUtil.h"

Message::Message() {}

Message::Message(int msg_num, string date_time, int from, int to,
		string message) {
	this->msg_number = msg_num;
	this->userFromID = from;
	this->userToID = to;
	this->message = message;
	this->date_time = date_time;
}

Message::~Message() {
}

string Message::serialize() {

	Json::Value message;
	message["message"]["msg_number"] = this->msg_number;
	message["message"]["fromID"] = this->userFromID;
	message["message"]["toID"] = this->userToID;
	message["message"]["date_time"] = this->date_time;
	message["message"]["text"] = this->message;

	return message.toStyledString();
}

void Message::deserialize(string serialized) {

	Json::Value parsedFromString;
	Json::Reader reader;
	reader.parse(serialized, parsedFromString);

	this->msg_number = (parsedFromString["message"]["msg_number"]).asInt();
	this->userFromID = (parsedFromString["message"]["fromID"]).asInt();
	this->userToID = (parsedFromString["message"]["toID"]).asInt();
	this->date_time = (parsedFromString["message"]["date_time"]).asString();
	this->message = (parsedFromString["message"]["text"]).asString();

}
