#include "Message.h"
#include "../../config.h"

Message::Message(const string& toDeserialize) {

	Json::Value parsedFromString;
	Json::Reader reader;
	bool wasParsed = reader.parse(toDeserialize, parsedFromString);

	if (not wasParsed) {
		NotSerializedDataException* e = new NotSerializedDataException(
				"'" + toDeserialize + "' is not a JSON serialized message.");
		throw *e;
	}

	this->userFromID =
			(parsedFromString[JSON_MSG_ROOT][JSON_MSG_FROM_VALUE]).asString();
	this->userToID =
			(parsedFromString[JSON_MSG_ROOT][JSON_MSG_TO_VALUE]).asString();
	this->date =
			(parsedFromString[JSON_MSG_ROOT][JSON_MSG_DATE_VALUE]).asString();
	this->time =
			(parsedFromString[JSON_MSG_ROOT][JSON_MSG_TIME_VALUE]).asString();
	this->message =
			(parsedFromString[JSON_MSG_ROOT][JSON_MSG_TEXT]).asString();
	this->sent =
			(parsedFromString[JSON_MSG_ROOT][JSON_MSG_SENT]).asBool();

	if (this->userFromID == this->userToID) {
		InvalidUsernameException *e = new InvalidUsernameException(
				"Can't add a message between a single user");
		throw *e;
	}
}

Message::Message(const string& from, const string& to, const string& message) {

	this->userFromID = from;
	this->userToID = to;
	this->message = message;
	this->date = Date::getDate();
	this->time = Time::getTime();
	this->sent = false;

	if (this->userFromID == this->userToID) {
		InvalidUsernameException *e = new InvalidUsernameException(
				"Can't add a message between a single user");
		throw *e;
	}
}

Message::~Message() {
}

string Message::serialize() const {

	Json::Value message;
	message[JSON_MSG_ROOT][JSON_MSG_FROM_VALUE] = this->userFromID;
	message[JSON_MSG_ROOT][JSON_MSG_TO_VALUE] = this->userToID;
	message[JSON_MSG_ROOT][JSON_MSG_DATE_VALUE] = this->date;
	message[JSON_MSG_ROOT][JSON_MSG_TIME_VALUE] = this->time;
	message[JSON_MSG_ROOT][JSON_MSG_TEXT] = this->message;
	message[JSON_MSG_ROOT][JSON_MSG_SENT] = this->sent;

	return message.toStyledString();
}

string Message::getText() const {
	return this->message;
}

string Message::getUserTo() const {
	return this->userToID;
}

string Message::getUserFrom() const {
	return this->userFromID;
}

string Message::getTime() const {
	return this->time;
}

string Message::getDate() const {
	return this->date;
}

bool Message::getSent() const{
	return this->sent;
}

void Message::setAsSent(){
	this->sent = true;
}
