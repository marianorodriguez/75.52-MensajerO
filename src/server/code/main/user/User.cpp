/*
 * User.cpp
 *
 *  Created on: 3/4/2015
 *      Author: marian
 */

#include "../../../include/main/user/User.h"

User::User(const string& username, const string& password) {
	this->loginToken = 0;
	this->loggedIn = false;
	this->lastTimeConnected = time(0);
	this->username = username;
	this->password = password;
	this->location = DEFAULT_USER_LOCATION;
	this->status = DEFAULT_USER_STATUS;
	this->hashedProfilePicture = DEFAULT_USER_PROFILE_PICTURE;
}

User::User(const string& serializedUser) {

	Json::Value parsedFromString;
	Json::Reader reader;
	bool wasParsed = reader.parse(serializedUser, parsedFromString);

	if (not wasParsed) {
		NotSerializedDataException exception(
				"'" + serializedUser + "' is not a JSON serialized user.");
		throw exception;
	}

	this->loginToken = parsedFromString[JSON_USER_LOGINTOKEN].asDouble();
	this->loggedIn = parsedFromString[JSON_USER_LOGGEDIN].asBool();
	this->lastTimeConnected = parsedFromString[JSON_USER_LASTTIME].asInt();
	this->username = parsedFromString[JSON_USER_NAME].asString();
	this->password = parsedFromString[JSON_USER_PWD].asString();
	this->location = parsedFromString[JSON_USER_LOCATION].asString();
	this->status = parsedFromString[JSON_USER_STATUS].asString();
	this->hashedProfilePicture =
			parsedFromString[JSON_USER_PROFILE_PICTURE].asString();

	int num_chats = parsedFromString[JSON_USER_CHATS_WITH].size();
	for (int i = 0; i < num_chats; i++) {
		this->addChatWithUser(
				parsedFromString[JSON_USER_CHATS_WITH][i].asString());
	}

}

User::~User() {
}

string User::serialize() const{

	Json::Value serializedUser;
	serializedUser[JSON_USER_LOGINTOKEN] = this->loginToken;
	serializedUser[JSON_USER_LOGGEDIN] = this->loggedIn;
	serializedUser[JSON_USER_LASTTIME] = this->lastTimeConnected;
	serializedUser[JSON_USER_NAME] = this->username;
	serializedUser[JSON_USER_PWD] = this->password;
	serializedUser[JSON_USER_LOCATION] = this->location;
	serializedUser[JSON_USER_STATUS] = this->status;
	serializedUser[JSON_USER_PROFILE_PICTURE] = this->hashedProfilePicture;

	for (unsigned int i = 0; i < this->hasChatsWith.size(); i++) {

		serializedUser[JSON_USER_CHATS_WITH][i] = this->hasChatsWith.at(i);

	}
	return serializedUser.toStyledString();
}

bool User::isConnected() const{
	return (time(0) - this->lastTimeConnected < MAXIMUM_IDLE_TIME);
}

bool User::isLoggedIn() const{
	return this->loggedIn;
}

void User::setLoggedIn(bool logged){
	this->loggedIn = logged;
}

double User::getLoginToken() const{
	return this->loginToken;
}

void User::setLoginToken(double token){
	this->loginToken = token;
}

string User::getUsername() const {
	return this->username;
}

string User::getPassword() const {
	return this->password;
}

string User::getLocation() const {
	return this->location;
}

string User::getStatus() const {
	return this->status;
}

string User::getProfilePicture() const {
	return this->hashedProfilePicture;
}

vector<string> User::getChats() const {
	return this->hasChatsWith;
}

void User::modifyProfilePicture(const string& newPP) {
	this->hashedProfilePicture = newPP;
}

void User::modifyLocation(const string& newLocation) {

	this->location = newLocation;
}

void User::modifyStatus(const string& newStatus) {

	this->status = newStatus;
}

void User::addChatWithUser(const string& username) {

	if (username == this->username) {
		string description = this->username + "can't have a chat with "
				+ this->username + ".";
		InvalidUsernameException exception(description);
		throw exception;
	}

	if (isChattingWith(username)) {
		string description = this->username + " is already chatting with "
				+ username + ".";
		InvalidUsernameException exception(description);
		throw exception;
	}

	this->hasChatsWith.push_back(username);
}

bool User::isChattingWith(const string& username) const {

	bool isChatting = false;

	for (unsigned int i = 0; i < hasChatsWith.size(); i++) {
		if (hasChatsWith.at(i) == username)
			isChatting = true;
	}

	return isChatting;
}

void User::setLastTimeConnected() {
	this->lastTimeConnected = time(0);
}
