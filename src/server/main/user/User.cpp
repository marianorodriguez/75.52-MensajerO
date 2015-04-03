/*
 * User.cpp
 *
 *  Created on: 3/4/2015
 *      Author: marian
 */

#include "User.h"

User::User(string username, string password) {

}

User::User(string serializedUser) {
}

User::~User() {

}

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

}

void User::modifyStatus(string newStatus) {

}

void User::addChatWithUser(string username) {

}

string User::encryptPassword(string plainPWD) {

	return "";
}
