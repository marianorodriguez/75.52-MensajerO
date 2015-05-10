/*
 * SendMessageServiceTest.cpp
 *
 *  Created on: 10/5/2015
 *      Author: marian
 */

#include "SendMessageServiceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(SendMessageServiceTest);

SendMessageServiceTest::SendMessageServiceTest() {}

SendMessageServiceTest::~SendMessageServiceTest() {}

void SendMessageServiceTest::setUp(){
	CppUnit::TestFixture::setUp();

	Database userDB(DATABASE_USERS_PATH);
	User user1("username1", "password1");
	User user2("username2", "password2");
	User user3("username3", "password3");
	user1.addChatWithUser("username2");
	user2.addChatWithUser("username1");
	vector<string> key1, key2, key3;
	key1.push_back("username1");
	key2.push_back("username2");
	key3.push_back("username3");
	userDB.write(key1, user1.serialize());
	userDB.write(key2, user2.serialize());
	userDB.write(key3, user3.serialize());

	Chat chat("username1", "username2");
	chat.addNewMessage(Message("username1", "username2", "firstMessage")); // username1 sends first message to username2
	chat.addNewMessage(Message("username1", "username2", "secondMessage"));	// username1 sends second message to username2
	chat.addNewMessage(Message("username2", "username1", "response"));// username2 replies username1

	Database chatDB(DATABASE_CHATS_PATH);
	vector<string> chatKey;
	chatKey.push_back("username1");
	chatKey.push_back("username2");
	chatDB.write(chatKey, chat.serialize());
}

void SendMessageServiceTest::tearDown(){
	CppUnit::TestFixture::tearDown();

	Database userDB(DATABASE_USERS_PATH);
	vector<string> key1, key2, key3;
	key1.push_back("username1");
	key2.push_back("username2");
	key3.push_back("username3");
	userDB.erase(key1);
	userDB.erase(key2);
	userDB.erase(key3);

	Database chatDB(DATABASE_CHATS_PATH);
	vector<string> chatKey;
	chatKey.push_back("username1");
	chatKey.push_back("username2");
	chatDB.erase(chatKey);
}

void SendMessageServiceTest::testShouldAddMessageToExistingChat(){

	Json::Value data;
	data[SERVICE_USERNAME] = "username1";
	data[SERVICE_PASSWORD] = "password1";
	data[SERVICE_SENDMESSAGE_USERNAME_TO] = "username2";
	data[SERVICE_SENDMESSAGE_MESSAGE] = "thirdMessage";

	Json::Value output = SendMessageService::doSendMessage(data);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == "");

	Database chatDB(DATABASE_CHATS_PATH);
	vector<string> chatKey;
	chatKey.push_back("username1");
	chatKey.push_back("username2");
	Chat chat(chatDB.read(chatKey));

	CPPUNIT_ASSERT(chat.getMessages().size() == 4);
}

void SendMessageServiceTest::testShouldCreateNewChat(){

	Json::Value data;
	data[SERVICE_USERNAME] = "username1";
	data[SERVICE_PASSWORD] = "password1";
	data[SERVICE_SENDMESSAGE_USERNAME_TO] = "username3";
	data[SERVICE_SENDMESSAGE_MESSAGE] = "firstMessage";

	Json::Value output = SendMessageService::doSendMessage(data);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == "");

	Database chatDB(DATABASE_CHATS_PATH);
	vector<string> chatKey;
	chatKey.push_back("username1");
	chatKey.push_back("username3");
	Chat chat(chatDB.read(chatKey));

	CPPUNIT_ASSERT(chat.getMessages().size() == 1);
}

void SendMessageServiceTest::testShouldThrowInvalidPassword(){

	Json::Value data;
	data[SERVICE_USERNAME] = "username1";
	data[SERVICE_PASSWORD] = "invalid_pass";
	data[SERVICE_SENDMESSAGE_USERNAME_TO] = "username2";
	data[SERVICE_SENDMESSAGE_MESSAGE] = "firstMessage";

	Json::Value output = SendMessageService::doSendMessage(data);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDPWD);
}

void SendMessageServiceTest::testShouldThrowInvalidUsername(){

	Json::Value data;
	data[SERVICE_USERNAME] = "usernameASDF";
	data[SERVICE_PASSWORD] = "password";
	data[SERVICE_SENDMESSAGE_USERNAME_TO] = "username2";
	data[SERVICE_SENDMESSAGE_MESSAGE] = "firstMessage";

	Json::Value output = SendMessageService::doSendMessage(data);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDUSER);
}