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
}

User::~User() {}

string User::serialize() {
	return "";
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


}

string User::encryptPassword(string plainPWD) {

	return md5(plainPWD);
}
