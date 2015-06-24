/*
 * SomethingForMeServiceTest.cpp
 *
 *  Created on: 9/5/2015
 *      Author: marian
 */

#include "services/SomethingForMeServiceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(SomethingForMeServiceTest);

SomethingForMeServiceTest::~SomethingForMeServiceTest(){

}

void SomethingForMeServiceTest::setUp() {
	ServiceTest::setUp();

	this->service = new SomethingForMeService(*userDB, *chatDB);

	User user1("username1", "password1");
	User user2("username2", "password2");
	user1.addChatWithUser("username2");
	user2.addChatWithUser("username1");

	vector<string> key1, key2;
	key1.push_back("username1");
	key2.push_back("username2");
	userDB->write(key1, user1.serialize());
	userDB->write(key2, user2.serialize());

	Chat chat("username1", "username2");
	chat.addNewMessage(Message("username1", "username2", "firstMessage")); // username1 sends first message to username2
	chat.addNewMessage(Message("username1", "username2", "secondMessage"));	// username1 sends second message to username2
	chat.addNewMessage(Message("username2", "username1", "response"));// username2 replies username1

	vector<string> chatKey;
	chatKey.push_back("username1");
	chatKey.push_back("username2");
	chatDB->write(chatKey, chat.serialize());
}

void SomethingForMeServiceTest::tearDown() {

	vector<string> key1, key2;
	key1.push_back("username1");
	key2.push_back("username2");
	userDB->erase(key1);
	userDB->erase(key2);

	vector<string> chatKey;
	chatKey.push_back("username1");
	chatKey.push_back("username2");
	chatDB->erase(chatKey);

	ServiceTest::tearDown();
}

void SomethingForMeServiceTest::testDoubleRequestShouldReturnNoMessages() {

	Json::Value data;
	data[SERVICE_USERNAME] = "username2";
	data[SERVICE_PASSWORD] = "password2";

	service->executeRequest(data.toStyledString());
	string output = service->executeRequest(data.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_WHAT].asString() == "");

	Json::Value messages = jsonOut.get(SERVICE_SOMETHINGFORME_MESSAGES.c_str(), "");
	CPPUNIT_ASSERT(messages.asString() == "");
}

void SomethingForMeServiceTest::testGetNewMessages() {

	Json::Value data;
	data[SERVICE_USERNAME] = "username2";
	data[SERVICE_PASSWORD] = "password2";

	string output = service->executeRequest(data.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_WHAT].asString() == "");

	Json::Value messages = jsonOut.get(SERVICE_SOMETHINGFORME_MESSAGES.c_str(), "null");

	CPPUNIT_ASSERT(messages.toStyledString() != "null");
	CPPUNIT_ASSERT(messages.size() == 2);


	Json::Value data2;
	data2[SERVICE_USERNAME] = "username1";
	data2[SERVICE_PASSWORD] = "password1";

	output = service->executeRequest(data2.toStyledString());
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_WHAT].asString() == "");

	Json::Value messages2 = jsonOut.get(SERVICE_SOMETHINGFORME_MESSAGES.c_str(), "");

	CPPUNIT_ASSERT(messages2.toStyledString() != "");
	CPPUNIT_ASSERT(messages2.size() == 1);
}

void SomethingForMeServiceTest::shouldThrowInvalidPassword() {

	Json::Value data;
	data[SERVICE_USERNAME] = "username2";
	data[SERVICE_PASSWORD] = "password_invalid";

	string output = service->executeRequest(data.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(
			jsonOut[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDPWD);
}

void SomethingForMeServiceTest::shouldThrowInvalidUsername() {

	Json::Value data;
	data[SERVICE_USERNAME] = "invalidUsername";
	data[SERVICE_PASSWORD] = "password2";

	string output = service->executeRequest(data.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(
			jsonOut[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDUSER);
}
