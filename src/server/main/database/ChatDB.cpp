/*
 * ChatDB.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: fran
 */

#include "ChatDB.h"

ChatDB::ChatDB() {
}

ChatDB::ChatDB(string path) : Database(path){
}

void ChatDB::writeChat(string user1,string user2, string value) {
	string key = this->getKey(user1,user2);
	this->write(key,value);
}

string ChatDB::readChat(string user1,string user2,bool* error){
	string key = this->getKey(user1,user2);
	return this->read(key,error);
}

string ChatDB::getKey(string user1,string user2){
	Json::Value key;
	if (user1 < user2) {
		key["key"]["user1"] = user1;
		key["key"]["user2"] = user2;
	} else {
		key["key"]["user1"] = user2;
		key["key"]["user2"] = user1;
	}

	return key.toStyledString();
}

void ChatDB::eraseChat(string user1,string user2){
	string key = this->getKey(user1,user2);
	this->erase(key);
}

ChatDB::~ChatDB() {
}

