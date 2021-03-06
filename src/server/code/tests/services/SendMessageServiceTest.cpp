/*
 * SendMessageServiceTest.cpp
 *
 *  Created on: 10/5/2015
 *      Author: marian
 */

#include "services/SendMessageServiceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(SendMessageServiceTest);

SendMessageServiceTest::~SendMessageServiceTest() {
}

void SendMessageServiceTest::setUp() {
	ServiceTest::setUp();

	this->service = new SendMessageService(*userDB, *chatDB);

	User user1("username1", "password1");
	User user2("username2", "password2");
	User user3("username3", "password3");
	user1.addChatWithUser("username2");
	user2.addChatWithUser("username1");
	std::vector<std::string> key1, key2, key3;
	key1.push_back("username1");
	key2.push_back("username2");
	key3.push_back("username3");
	userDB->write(key1, user1.serialize());
	userDB->write(key2, user2.serialize());
	userDB->write(key3, user3.serialize());

	Chat chat("username1", "username2");
	chat.addNewMessage(Message("username1", "username2", "firstMessage")); // username1 sends first message to username2
	chat.addNewMessage(Message("username1", "username2", "secondMessage"));	// username1 sends second message to username2
	chat.addNewMessage(Message("username2", "username1", "response"));// username2 replies username1

	std::vector<std::string> chatKey;
	chatKey.push_back("username1");
	chatKey.push_back("username2");
	chatDB->write(chatKey, chat.serialize());
}

void SendMessageServiceTest::tearDown() {

	std::vector<std::string> key1, key2, key3;
	key1.push_back("username1");
	key2.push_back("username2");
	key3.push_back("username3");
	userDB->erase(key1);
	userDB->erase(key2);
	userDB->erase(key3);

	std::vector<std::string> chatKey;
	chatKey.push_back("username1");
	chatKey.push_back("username2");
	chatDB->erase(chatKey);

	ServiceTest::tearDown();
}

void SendMessageServiceTest::testGetUri() {
	CPPUNIT_ASSERT(this->service->getUri() == "sendMessage");
}

void SendMessageServiceTest::testShouldAddMessageToExistingChat() {

	Json::Value data;
	data[SERVICE_USERNAME] = "username1";
	data[SERVICE_PASSWORD] = "password1";
	data[SERVICE_SENDMESSAGE_USERNAME_TO] = "username2";
	data[SERVICE_SENDMESSAGE_MESSAGE] = "thirdMessage";

	string output = service->executeRequest(data.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_WHAT].asString() == "");

	std::vector<std::string> chatKey;
	chatKey.push_back("username1");
	chatKey.push_back("username2");
	Chat chat(chatDB->read(chatKey));

	CPPUNIT_ASSERT(chat.getMessages().size() == 4);
}

void SendMessageServiceTest::testShouldCreateNewChat() {

	Json::Value data;
	data[SERVICE_USERNAME] = "username1";
	data[SERVICE_PASSWORD] = "password1";
	data[SERVICE_SENDMESSAGE_USERNAME_TO] = "username3";
	data[SERVICE_SENDMESSAGE_MESSAGE] = "firstMessage";

	string output = service->executeRequest(data.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_WHAT].asString() == "");

	std::vector<std::string> chatKey;
	chatKey.push_back("username1");
	chatKey.push_back("username3");
	Chat chat(chatDB->read(chatKey));

	CPPUNIT_ASSERT(chat.getMessages().size() == 1);
}

void SendMessageServiceTest::testShouldThrowInvalidPassword() {

	Json::Value data;
	data[SERVICE_USERNAME] = "username1";
	data[SERVICE_PASSWORD] = "invalid_pass";
	data[SERVICE_SENDMESSAGE_USERNAME_TO] = "username2";
	data[SERVICE_SENDMESSAGE_MESSAGE] = "firstMessage";

	string output = service->executeRequest(data.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(
			jsonOut[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDPWD);
}

void SendMessageServiceTest::testShouldThrowInvalidUsername() {

	Json::Value data;
	data[SERVICE_USERNAME] = "usernameASDF";
	data[SERVICE_PASSWORD] = "password";
	data[SERVICE_SENDMESSAGE_USERNAME_TO] = "username2";
	data[SERVICE_SENDMESSAGE_MESSAGE] = "firstMessage";

	string output = service->executeRequest(data.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(
			jsonOut[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDUSER);
}
