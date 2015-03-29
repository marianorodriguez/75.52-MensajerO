/*
 * Message.cpp
 *
 *  Created on: 29/3/2015
 *      Author: marian
 */

#include "Message.h"
#include "../config.h"

Message::Message() {

}

Message::Message(int from, int to, string message) {

	this->userFromID = from;
	this->userToID = to;
	this->message = message;
}

Message::~Message() {
}

string Message::serialize() {

	string from = StringUtil::int2string(this->userFromID);
	string to = StringUtil::int2string(this->userToID);

	string serialized = from + MESSAGE_FIELD_SEPARATOR + to
			+ MESSAGE_FIELD_SEPARATOR + this->message;

	return serialized;
}

void Message::deserialize(string serialized) {

	vector<string> vecString = StringUtil::split(serialized,
	MESSAGE_FIELD_SEPARATOR);

	this->userFromID = StringUtil::str2int(vecString.at(0));
	this->userToID = StringUtil::str2int(vecString.at(1));
	this->message = vecString.at(2);
}
