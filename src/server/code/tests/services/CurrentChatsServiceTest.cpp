/*
 * CurrentChatsServiceTest.cpp
 *
 *  Created on: 9/5/2015
 *      Author: marian
 */

#include "services/CurrentChatsServiceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(CurrentChatsServiceTest);

CurrentChatsServiceTest::~CurrentChatsServiceTest() {}

void CurrentChatsServiceTest::setUp(){
	ServiceTest::setUp();
	this->service = new CurrentChatsService(*userDB, *chatDB);

	User user1("username1", "password1");
	User user2("username2", "password2");
	User user3("username3", "password3");
	user1.addChatWithUser("username2");
	user1.addChatWithUser("username3");

	vector<string> key1;
	key1.push_back("username1");
	userDB->write(key1, user1.serialize());

	Chat chat12("username1", "username2");
	chat12.addNewMessage(Message("username1", "username2", "firstMessage")); // username1 sends first message to username2
	chat12.addNewMessage(Message("username1", "username2", "secondMessage"));	// username1 sends second message to username2
	chat12.addNewMessage(Message("username2", "username1", "response"));// username2 replies username1


	Chat chat13("username1", "username3");
	chat13.addNewMessage(Message("username3", "username1", "firstMessage")); // username3 sends first message to username1
	chat13.addNewMessage(Message("username3", "username1", "secondMessage"));	// username3 sends second message to username1
	chat13.addNewMessage(Message("username1", "username3", "response"));// username1 replies username3

	vector<string> chatKey;
	chatKey.push_back("username1");
	chatKey.push_back("username2");
	chatDB->write(chatKey, chat12.serialize());

	chatKey.clear();
	chatKey.push_back("username1");
	chatKey.push_back("username3");
	chatDB->write(chatKey, chat13.serialize());
}

void CurrentChatsServiceTest::tearDown(){
	vector<string> key1;
	key1.push_back("username1");
	userDB->erase(key1);

	vector<string> chatKey;
	chatKey.push_back("username1");
	chatKey.push_back("username2");
	chatDB->erase(chatKey);

	chatKey.clear();
	chatKey.push_back("username1");
	chatKey.push_back("username3");
	chatDB->erase(chatKey);

	ServiceTest::tearDown();
}

void CurrentChatsServiceTest::testShouldGetUri(){
	CPPUNIT_ASSERT(this->service->getUri() == "currentChats");
}

void CurrentChatsServiceTest::testShouldGetCurrentChats(){

	Json::Value data;
	data[SERVICE_USERNAME] = "username1";
	data[SERVICE_PASSWORD] = "password1";

	string output = service->executeRequest(data.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_CURRENTCHATS_CHATS].size() == 2);
	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_WHAT].asString() == "");
}

void CurrentChatsServiceTest::testShouldThrowInvalidPassword(){
	Json::Value data;
	data[SERVICE_USERNAME] = "username1";
	data[SERVICE_PASSWORD] = "password1alr";

	string output = service->executeRequest(data.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDPWD);
}

void CurrentChatsServiceTest::testShouldThrowInvalidUsername(){

	Json::Value data;
	data[SERVICE_USERNAME] = "username1asd";
	data[SERVICE_PASSWORD] = "password1";

	string output = service->executeRequest(data.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDUSER);
}

void CurrentChatsServiceTest::shouldGetEmptyChatList(){

	Json::Value data;
	data[SERVICE_USERNAME] = "username3";
	data[SERVICE_PASSWORD] = "password3";

	string output = service->executeRequest(data.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_CURRENTCHATS_CHATS].size() == 0);
}
