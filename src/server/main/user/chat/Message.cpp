#include "Message.h"
#include "../../config.h"

Message::Message(string toDeserialize) {

	Json::Value parsedFromString;
	Json::Reader reader;
	bool wasParsed = reader.parse(toDeserialize, parsedFromString);

	if (not wasParsed){
		NotSerializedDataException* e = new NotSerializedDataException("'" + toDeserialize + "' is not a JSON serialized message.");
		throw *e;
	}

	this->userFromID =
			(parsedFromString[JSON_MSG_ROOT][JSON_MSG_FROM_VALUE]).asString();
	this->userToID =
			(parsedFromString[JSON_MSG_ROOT][JSON_MSG_TO_VALUE]).asString();
	this->date_time =
			(parsedFromString[JSON_MSG_ROOT][JSON_MSG_DATE_TIME_VALUE]).asString();
	this->message =
			(parsedFromString[JSON_MSG_ROOT][JSON_MSG_TEXT]).asString();

	if(this->userFromID == this->userToID){
		InvalidUsernameException *e = new InvalidUsernameException("Can't add a message between a single user");
		throw *e;
	}
}

Message::Message(string date_time, string from, string to, string message) {

	this->userFromID = from;
	this->userToID = to;
	this->message = message;
	this->date_time = date_time; //TODO automatizar la fecha y hora

	if(this->userFromID == this->userToID){
		InvalidUsernameException *e = new InvalidUsernameException("Can't add a message between a single user");
		throw *e;
	}
}

Message::~Message() {
}

string Message::serialize() {

	Json::Value message;
	message[JSON_MSG_ROOT][JSON_MSG_FROM_VALUE] = this->userFromID;
	message[JSON_MSG_ROOT][JSON_MSG_TO_VALUE] = this->userToID;
	message[JSON_MSG_ROOT][JSON_MSG_DATE_TIME_VALUE] = this->date_time;
	message[JSON_MSG_ROOT][JSON_MSG_TEXT] = this->message;

	return message.toStyledString();
}

string Message::getText(){
	return this->message;
}

string Message::getUserTo(){
	return this->userToID;
}

string Message::getUserFrom(){
	return this->userFromID;
}
