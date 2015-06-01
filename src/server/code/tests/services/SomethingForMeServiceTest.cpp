/*
 * SomethingForMeServiceTest.cpp
 *
 *  Created on: 9/5/2015
 *      Author: marian
 */

#include "../../include/tests/services/SomethingForMeServiceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(SomethingForMeServiceTest);

SomethingForMeServiceTest::SomethingForMeServiceTest() {
}

SomethingForMeServiceTest::~SomethingForMeServiceTest() {
}

void SomethingForMeServiceTest::setUp() {
	CppUnit::TestFixture::setUp();

	User user1("username1", "password1");
	User user2("username2", "password2");
	user1.addChatWithUser("username2");
	user2.addChatWithUser("username1");

	Database userDB(DATABASE_USERS_PATH);
	vector<string> key1, key2;
	key1.push_back("username1");
	key2.push_back("username2");
	userDB.write(key1, user1.serialize());
	userDB.write(key2, user2.serialize());

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

void SomethingForMeServiceTest::tearDown() {
	CppUnit::TestFixture::tearDown();

	Database userDB(DATABASE_USERS_PATH);
	vector<string> key1, key2;
	key1.push_back("username1");
	key2.push_back("username2");
	userDB.erase(key1);
	userDB.erase(key2);

	Database chatDB(DATABASE_CHATS_PATH);
	vector<string> chatKey;
	chatKey.push_back("username1");
	chatKey.push_back("username2");
	chatDB.erase(chatKey);
}

void SomethingForMeServiceTest::testDoubleRequestShouldReturnNoMessages() {

	Json::Value data;
	data[SERVICE_USERNAME] = "username2";
	data[SERVICE_PASSWORD] = "password2";

	SomethingForMeService::doSomethingForMe(data);
	Json::Value output = SomethingForMeService::doSomethingForMe(data);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == "");

	Json::Value messages = output.get(SERVICE_SOMETHINGFORME_MESSAGES.c_str(), "");
	CPPUNIT_ASSERT(messages.asString() == "");
}

void SomethingForMeServiceTest::testGetNewMessages() {

	Json::Value data;
	data[SERVICE_USERNAME] = "username2";
	data[SERVICE_PASSWORD] = "password2";

	Json::Value output = SomethingForMeService::doSomethingForMe(data);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == "");

	Json::Value messages = output.get(SERVICE_SOMETHINGFORME_MESSAGES.c_str(), "null");

	CPPUNIT_ASSERT(messages.toStyledString() != "null");
	CPPUNIT_ASSERT(messages.size() == 2);


	Json::Value data2;
	data2[SERVICE_USERNAME] = "username1";
	data2[SERVICE_PASSWORD] = "password1";

	Json::Value output2 = SomethingForMeService::doSomethingForMe(data2);

	CPPUNIT_ASSERT(output2[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(output2[SERVICE_OUT_WHAT].asString() == "");

	Json::Value messages2 = output2.get(SERVICE_SOMETHINGFORME_MESSAGES.c_str(), "");

	CPPUNIT_ASSERT(messages2.toStyledString() != "");
	CPPUNIT_ASSERT(messages2.size() == 1);
}

void SomethingForMeServiceTest::shouldThrowInvalidPassword() {

	Json::Value data;
	data[SERVICE_USERNAME] = "username2";
	data[SERVICE_PASSWORD] = "password_invalid";

	Json::Value output = SomethingForMeService::doSomethingForMe(data);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(
			output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDPWD);
}

void SomethingForMeServiceTest::shouldThrowInvalidUsername() {

	Json::Value data;
	data[SERVICE_USERNAME] = "invalidUsername";
	data[SERVICE_PASSWORD] = "password2";

	Json::Value output = SomethingForMeService::doSomethingForMe(data);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(
			output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDUSER);
}
