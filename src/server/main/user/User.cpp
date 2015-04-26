/*
 * User.cpp
 *
 *  Created on: 3/4/2015
 *      Author: marian
 */

#include "User.h"
#include "utilities/MD5.h"

User::User(const string& username, const string& password) {

	this->username = username;
	this->password = password;
	this->numberOfChats = 0;
	this->location = DEFAULT_USER_LOCATION;
	this->status = DEFAULT_USER_STATUS;
	this->hashedProfilePicture = DEFAULT_USER_PROFILE_PICTURE;
}

User::User(const string& serializedUser) {

	Json::Value parsedFromString;
	Json::Reader reader;
	bool wasParsed = reader.parse(serializedUser, parsedFromString);

	if (not wasParsed) {
		NotSerializedDataException exception("'" + serializedUser +
						"' is not a JSON serialized user.");
		throw exception;
	}

	this->username =
			parsedFromString[JSON_USER_ROOT][JSON_USER_NAME].asString();
	this->password =
			parsedFromString[JSON_USER_ROOT][JSON_USER_PWD].asString();
	this->location =
			parsedFromString[JSON_USER_ROOT][JSON_USER_LOCATION].asString();
	this->status =
			parsedFromString[JSON_USER_ROOT][JSON_USER_STATUS].asString();
	this->hashedProfilePicture =
			parsedFromString[JSON_USER_ROOT][JSON_USER_PROFILE_PICTURE].asString();
	this->numberOfChats = 0;

	int num_chats =
			parsedFromString[JSON_USER_ROOT][JSON_USER_NUM_CHAT].asInt();
	for (int i = 0; i < num_chats; i++) {
		this->addChatWithUser(
				parsedFromString[JSON_USER_ROOT][JSON_USER_CHATS_WITH][i].asString());
	}

}

User::~User() {
}

string User::serialize()const {

	Json::Value serializedUser;
	serializedUser[JSON_USER_ROOT][JSON_USER_NAME] = this->username;
	serializedUser[JSON_USER_ROOT][JSON_USER_PWD] = this->password;
	serializedUser[JSON_USER_ROOT][JSON_USER_LOCATION] = this->location;
	serializedUser[JSON_USER_ROOT][JSON_USER_STATUS] = this->status;
	serializedUser[JSON_USER_ROOT][JSON_USER_NUM_CHAT] = this->numberOfChats;
	serializedUser[JSON_USER_ROOT][JSON_USER_PROFILE_PICTURE] =
			this->hashedProfilePicture;

	for (int i = 0; i < this->numberOfChats; i++) {

		serializedUser[JSON_USER_ROOT][JSON_USER_CHATS_WITH][i] =
				this->hasChatsWith.at(i);

	}

	return serializedUser.toStyledString();
}

string User::getUsername() const {
	return this->username;
}

string User::getLocation() const {
	return this->location;
}

string User::getStatus() const {
	return this->status;
}

string User::getHashedProfilePicture() const {
	return this->hashedProfilePicture;
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
	this->numberOfChats++;

}

bool User::isChattingWith(const string& username) const {

	bool isChatting = false;

	for (unsigned int i = 0; i < hasChatsWith.size(); i++) {
		if (hasChatsWith.at(i) == username)
			isChatting = true;
	}

	return isChatting;
}
