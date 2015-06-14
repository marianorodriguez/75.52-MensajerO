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
	User user2("username2", "password2");
	User user3("username3", "password3");
	user1.setConnected(true);
	user2.setConnected(true);
	user3.setConnected(true);

	vector<string> key1, key2, key3;
	key1.push_back("username1_bc");
	key2.push_back("username2");
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
	key2.push_back("username2");
	key3.push_back("username3");
	userDB.erase(key1);
	userDB.erase(key2);
	userDB.erase(key3);
	userDB.close();
}

void BroadcastServiceTest::testShouldDoBroadcast(){
	Json::Value input;
	input[SERVICE_USERNAME] = "username1_bc";
	input[SERVICE_PASSWORD] = "password1";
	input[SERVICE_SENDMESSAGE_MESSAGE] = "text to broadcast";

	Json::Value output = BroadcastService::doBroadcast(input);

	Database userDB(DATABASE_USERS_PATH);
	vector<string> key; key.push_back("username2");
	User user2 = userDB.read(key);
	key.clear(); key.push_back("username3");
	User user3 = userDB.read(key);

	CPPUNIT_ASSERT(user2.getChats().size() == 1);
	CPPUNIT_ASSERT(user3.getChats().size() == 1);
	userDB.close();
}

void BroadcastServiceTest::testShouldNotSendBroadcastToOfflineUsers(){

	Json::Value input;
	input[SERVICE_USERNAME] = "username1_bc";
	input[SERVICE_PASSWORD] = "password1";
	input[SERVICE_SENDMESSAGE_MESSAGE] = "text to broadcast";

	Database userDB(DATABASE_USERS_PATH);
	User user4("username4", "password4");
	user4.setConnected(false);
	vector<string> key4;
	key4.push_back("username4");
	userDB.write(key4, user4.serialize());
	userDB.close();

	CPPUNIT_ASSERT(user4.getChats().size() == 0);

	Json::Value output = BroadcastService::doBroadcast(input);

	Database DB(DATABASE_USERS_PATH);
	User user4Offline(DB.read(key4));
	CPPUNIT_ASSERT(user4Offline.getChats().size() == 0);
	DB.erase(key4);
	DB.close();
}

void BroadcastServiceTest::testShouldBeInvalidPassword(){
	Json::Value input;
	input[SERVICE_USERNAME] = "username1_bc";
	input[SERVICE_PASSWORD] = "password1asd";
	input[SERVICE_SENDMESSAGE_MESSAGE] = "text to broadcast";

	Json::Value output = BroadcastService::doBroadcast(input);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDPWD);
}

void BroadcastServiceTest::testShouldBeInvalidUsername(){
	Json::Value input;
	input[SERVICE_USERNAME] = "username1asd";
	input[SERVICE_PASSWORD] = "password1";
	input[SERVICE_SENDMESSAGE_MESSAGE] = "text to broadcast";

	Json::Value output = BroadcastService::doBroadcast(input);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDUSER);
}

