/*
 * BroadcastServiceTest.cpp
 *
 *  Created on: 14/6/2015
 *      Author: marian
 */

#include "services/BroadcastServiceTest.h"
CPPUNIT_TEST_SUITE_REGISTRATION(BroadcastServiceTest);

BroadcastServiceTest::BroadcastServiceTest(){};
BroadcastServiceTest::~BroadcastServiceTest(){};

void BroadcastServiceTest::setUp(){
	CppUnit::TestFixture::setUp();

	Database userDB(DATABASE_USERS_PATH);
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
	userDB.write(key1, user1.serialize());
	userDB.write(key2, user2.serialize());
	userDB.write(key3, user3.serialize());
	CPPUNIT_ASSERT(user2.getChats().size() == 0);
	CPPUNIT_ASSERT(user3.getChats().size() == 0);
	userDB.close();
}

void BroadcastServiceTest::tearDown(){
	CppUnit::TestFixture::tearDown();

	Database userDB(DATABASE_USERS_PATH);
	vector<string> key1, key2, key3;
	key1.push_back("username1_bc");
	key2.push_back("secondUser");
	key3.push_back("username3");
	userDB.erase(key1);
	userDB.erase(key2);
	userDB.erase(key3);
	userDB.close();
}

void BroadcastServiceTest::testShouldDoBroadcast(){
	Database userDb(DATABASE_USERS_PATH);
	BroadcastService service(userDb);
	Json::Value input;
	input[SERVICE_USERNAME] = "username1_bc";
	input[SERVICE_PASSWORD] = "password1";
	input[SERVICE_SENDMESSAGE_MESSAGE] = "text to broadcast";

	Json::Value output = service.doBroadcast(input);
	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == true);
	vector<string> key2, key3;
	key2.push_back("secondUser");
	User user2 = userDb.read(key2);
	key3.push_back("username3");
	User user3 = userDb.read(key3);
	CPPUNIT_ASSERT(user2.getChats().size() == 1);
	CPPUNIT_ASSERT(user3.getChats().size() == 1);
	userDb.close();

	Database chatDB(DATABASE_CHATS_PATH);
	vector<string> keyChat1, keyChat2;
	keyChat1.push_back("username1_bc");
	keyChat1.push_back("secondUser");
	keyChat2.push_back("username1_bc");
	keyChat2.push_back("username3");
	chatDB.erase(keyChat1);
	chatDB.erase(keyChat2);
	chatDB.close();
}

void BroadcastServiceTest::testShouldBeInvalidPassword(){
	Database userDb(DATABASE_USERS_PATH);
	BroadcastService service(userDb);
	Json::Value input;
	input[SERVICE_USERNAME] = "username1_bc";
	input[SERVICE_PASSWORD] = "password1asd";
	input[SERVICE_SENDMESSAGE_MESSAGE] = "text to broadcast";

	Json::Value output = service.doBroadcast(input);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDPWD);
}

void BroadcastServiceTest::testShouldBeInvalidUsername(){
	Database userDb(DATABASE_USERS_PATH);
	BroadcastService service(userDb);
	Json::Value input;
	input[SERVICE_USERNAME] = "username1asd";
	input[SERVICE_PASSWORD] = "password1";
	input[SERVICE_SENDMESSAGE_MESSAGE] = "text to broadcast";

	Json::Value output = service.doBroadcast(input);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDUSER);
}

