/*
 * UsersServiceTest.cpp
 *
 *  Created on: 10/5/2015
 *      Author: marian
 */

#include "services/UsersServiceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(UsersServiceTest);

UsersServiceTest::UsersServiceTest() {}

UsersServiceTest::~UsersServiceTest() {}

void UsersServiceTest::setUp(){
	CppUnit::TestFixture::setUp();

	Database userDB(DATABASE_USERS_PATH);
	User user1("username123", "password123");
	User user2("usernameASD", "passwordASD");
	User user3("usernameQWE", "passwordQWE");
	User user4("usernameZXC", "passwordZXC");
	user1.setLoggedIn(true); user1.setLoginToken(0);
	user2.setLoggedIn(true); user2.setLoginToken(0);
	user3.setLoggedIn(true); user3.setLoginToken(0);
	user4.setLoggedIn(true); user4.setLoginToken(0);

	vector<string> key1, key2, key3, key4;
	key1.push_back("username123");
	key2.push_back("usernameASD");
	key3.push_back("usernameQWE");
	key4.push_back("usernameZXC");

	userDB.write(key1, user1.serialize());
	userDB.write(key2, user2.serialize());
	userDB.write(key3, user3.serialize());
	userDB.write(key4, user4.serialize());
	userDB.close();
}

void UsersServiceTest::tearDown(){
	CppUnit::TestFixture::tearDown();

	Database userDB(DATABASE_USERS_PATH);
	vector<string> key1, key2, key3, key4;
	key1.push_back("username123");
	key2.push_back("usernameASD");
	key3.push_back("usernameQWE");
	key4.push_back("usernameZXC");

	userDB.erase(key1);
	userDB.erase(key2);
	userDB.erase(key3);
	userDB.erase(key4);
	userDB.close();
}

void UsersServiceTest::testLoggedOutUser(){

	Json::Value data;
	data[SERVICE_USERNAME] = "username1";
	data[SERVICE_PASSWORD] = "password1";
	data[SERVICE_TOKEN] = 0;

	Database userDB(DATABASE_USERS_PATH);
	User user1("username1", "password1");
	user1.setLastTimeConnected();
	user1.setLoggedIn(false); user1.setLoginToken(0);
	vector<string> key; key.push_back("username1");
	userDB.write(key, user1.serialize());
	userDB.close();

	Json::Value output =  UsersService::doUsers(data);
	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_NOTLOGGEDUSER);

	Database DB(DATABASE_USERS_PATH);
	DB.erase(key);
	DB.close();
}

void UsersServiceTest::testShouldReturnAllUsersInDB(){
	Json::Value data;
	data[SERVICE_USERNAME] = "usernameASD";
	data[SERVICE_PASSWORD] = "passwordASD";
	data[SERVICE_TOKEN] = 0;

	Json::Value output = UsersService::doUsers(data);

	CPPUNIT_ASSERT(output[SERVICE_USERS_NAME].size() >= 4);
}

void UsersServiceTest::testShouldThrowInvalidPassword(){
	Json::Value data;
	data[SERVICE_USERNAME] = "usernameASD";
	data[SERVICE_PASSWORD] = "passwordASDFGH";
	data[SERVICE_TOKEN] = 0;

	Json::Value output = UsersService::doUsers(data);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDPWD);
}

void UsersServiceTest::testShouldThrowInvalidUsername(){
	Json::Value data;
	data[SERVICE_USERNAME] = "usernameASDAJSDG";
	data[SERVICE_PASSWORD] = "passwordASD";
	data[SERVICE_TOKEN] = 0;

	Json::Value output = UsersService::doUsers(data);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDUSER);

}
