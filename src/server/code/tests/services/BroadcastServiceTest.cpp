/*
 * BroadcastServiceTest.cpp
 *
 *  Created on: 14/6/2015
 *      Author: marian
 */

#include "services/BroadcastServiceTest.h"
CPPUNIT_TEST_SUITE_REGISTRATION(BroadcastServiceTest);

BroadcastServiceTest::~BroadcastServiceTest(){};

void BroadcastServiceTest::setUp(){
	ServiceTest::setUp();
	this->service = new BroadcastService(*this->userDB, *this->chatDB);

	User user1("username1_bc", "password1");
	User user2("secondUser", "password2");
	User user3("username3", "password3");
	user1.setLastTimeConnected();
	user2.setLastTimeConnected();
	user3.setLastTimeConnected();

	vector<string> key1, key2, key3;
	key1.push_back("username1_bc");
	key2.push_back("secondUser");
	key3.push_back("username3");
	userDB->write(key1, user1.serialize());
	userDB->write(key2, user2.serialize());
	userDB->write(key3, user3.serialize());
	CPPUNIT_ASSERT(user2.getChats().size() == 0);
	CPPUNIT_ASSERT(user3.getChats().size() == 0);
}

void BroadcastServiceTest::tearDown(){

	vector<string> key1, key2, key3;
	key1.push_back("username1_bc");
	key2.push_back("secondUser");
	key3.push_back("username3");
	userDB->erase(key1);
	userDB->erase(key2);
	userDB->erase(key3);

	std::vector<std::string> keyChat1, keyChat2;
	keyChat1.push_back("username1_bc");
	keyChat1.push_back("secondUser");
	keyChat2.push_back("username1_bc");
	keyChat2.push_back("username3");
	chatDB->erase(keyChat1);
	chatDB->erase(keyChat2);

	ServiceTest::tearDown();
}

void BroadcastServiceTest::testShouldGetUri(){
	CPPUNIT_ASSERT(this->service->getUri() == "broadcast");
}

void BroadcastServiceTest::testShouldDoBroadcast(){

	Json::Value input;
	input[SERVICE_USERNAME] = "username1_bc";
	input[SERVICE_PASSWORD] = "password1";
	input[SERVICE_SENDMESSAGE_MESSAGE] = "text to broadcast";

	string output = service->executeRequest(input.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);
	CPPUNIT_ASSERT(jsonOut.get(SERVICE_OUT_OK,"").asBool() == true);
	std::vector<std::string> key2, key3;
	key2.push_back("secondUser");
	User user2 = userDB->read(key2);
	key3.push_back("username3");
	User user3 = userDB->read(key3);
	int user2Chats = user2.getChats().size();
	int user3Chats = user3.getChats().size();

	CPPUNIT_ASSERT_EQUAL(1, user2Chats);
	CPPUNIT_ASSERT_EQUAL(1, user3Chats);
}

void BroadcastServiceTest::testShouldBeInvalidPassword(){

	Json::Value input;
	input[SERVICE_USERNAME] = "username1_bc";
	input[SERVICE_PASSWORD] = "password1asd";
	input[SERVICE_SENDMESSAGE_MESSAGE] = "text to broadcast";

	string output = service->executeRequest(input.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDPWD);
}

void BroadcastServiceTest::testShouldBeInvalidUsername(){

	Json::Value input;
	input[SERVICE_USERNAME] = "username1asd";
	input[SERVICE_PASSWORD] = "password1";
	input[SERVICE_SENDMESSAGE_MESSAGE] = "text to broadcast";

	string output = service->executeRequest(input.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDUSER);
}

