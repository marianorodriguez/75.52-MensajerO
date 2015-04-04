/*
 * User.cpp
 *
 *  Created on: 3/4/2015
 *      Author: marian
 */

#include "User.h"

User::User(string username, string password) {

	this->username = username;
	this->hashedPWD = encryptPassword(password);
	this->numberOfChats = 0;
	this->location = DEFAULT_USER_LOCATION;
	this->status = DEFAULT_USER_STATUS;
}

User::User(string serializedUser) {

	Json::Value parsedFromString;
	Json::Reader reader;
	bool wasParsed = reader.parse(serializedUser, parsedFromString);

	if (not wasParsed) {
		NotSerializedDataException* e = new NotSerializedDataException(
				"'" + serializedUser + "' is not a JSON serialized user.");
		throw *e;
	}

	this->username = parsedFromString[JSON_USER_ROOT][JSON_USER_NAME].asString();
	this->hashedPWD = parsedFromString[JSON_USER_ROOT][JSON_USER_PWD].asString();
	this->location = parsedFromString[JSON_USER_ROOT][JSON_USER_LOCATION].asString();
	this->status = parsedFromString[JSON_USER_ROOT][JSON_USER_STATUS].asString();
	this->numberOfChats = 0;

	int num_chats = parsedFromString[JSON_USER_ROOT][JSON_USER_NUM_CHAT].asInt();
	for(int i=0; i< num_chats; i++){
		this->addChatWithUser(parsedFromString[JSON_USER_ROOT][JSON_USER_CHATS_WITH][i].asString());
	}

}

User::~User() {}

string User::serialize() {

	Json::Value serializedUser;
	serializedUser[JSON_USER_ROOT][JSON_USER_NAME] = this->username;
	serializedUser[JSON_USER_ROOT][JSON_USER_PWD] = this->hashedPWD;
	serializedUser[JSON_USER_ROOT][JSON_USER_LOCATION] = this->location;
	serializedUser[JSON_USER_ROOT][JSON_USER_STATUS] = this->status;
	serializedUser[JSON_USER_ROOT][JSON_USER_NUM_CHAT] = this->numberOfChats;

	for(int i=0; i< this->numberOfChats; i++){

		serializedUser[JSON_USER_ROOT][JSON_USER_CHATS_WITH][i] = this->hasChatsWith.at(i);

	}

	return serializedUser.toStyledString();
}

string User::getUsername() {
	return this->username;
}

string User::getHashedPWD() {
	return this->hashedPWD;
}

string User::getLocation() {
	return this->location;
}

string User::getStatus() {
	return this->status;
}

void User::modifyLocation(string newLocation) {

	this->location = newLocation;
}

void User::modifyStatus(string newStatus) {

	this->status = newStatus;
}

void User::addChatWithUser(string username) {

	if(username == this->username){
		string description = this->username + "can't have a chat with " + this->username + ".";
		InvalidUsernameException *e = new InvalidUsernameException(description);
		throw *e;
	}

	if(isChattingWith(username)){
		string description = this->username + " is already chatting with " + username + ".";
		InvalidUsernameException *e = new InvalidUsernameException(description);
		throw *e;
	}

	this->hasChatsWith.push_back(username);
	this->numberOfChats++;

}

string User::encryptPassword(string plainPWD) {

	return md5(plainPWD);
}

bool User::isChattingWith(string username){

	bool isChatting = false;

	for(unsigned int i=0; i< hasChatsWith.size(); i++){
		if(hasChatsWith.at(i) == username) isChatting = true;
	}

	return isChatting;
}
