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

	vector<string> key1, key2, key3, key4;
	key1.push_back("username123");
	key2.push_back("usernameASD");
	key3.push_back("usernameQWE");
	key4.push_back("usernameZXC");

	userDB.write(key1, user1.serialize());
	userDB.write(key2, user2.serialize());
	userDB.write(key3, user3.serialize());
	userDB.write(key4, user4.serialize());

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
}

void UsersServiceTest::testShouldReturnAllUsersInDB(){
	Json::Value data;
	data[SERVICE_USERNAME] = "usernameASD";
	data[SERVICE_PASSWORD] = "passwordASD";

	Json::Value output = UsersService::doUsers(data);

	CPPUNIT_ASSERT(output[SERVICE_USERS_NAME].size() == 4);
}

void UsersServiceTest::testShouldThrowInvalidPassword(){
	Json::Value data;
	data[SERVICE_USERNAME] = "usernameASD";
	data[SERVICE_PASSWORD] = "passwordASDFGH";

	Json::Value output = UsersService::doUsers(data);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDPWD);
}

void UsersServiceTest::testShouldThrowInvalidUsername(){
	Json::Value data;
	data[SERVICE_USERNAME] = "usernameASDAJSDG";
	data[SERVICE_PASSWORD] = "passwordASD";

	Json::Value output = UsersService::doUsers(data);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDUSER);

}
