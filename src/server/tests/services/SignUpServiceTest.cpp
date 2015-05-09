/*
 * SignUpServiceTest.cpp
 *
 *  Created on: 9/5/2015
 *      Author: marian
 */

#include "SignUpServiceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(SignUpServiceTest);

SignUpServiceTest::SignUpServiceTest() {}

SignUpServiceTest::~SignUpServiceTest() {
}

void SignUpServiceTest::setUp(){
	TestFixture::setUp();

	Database DB(DATABASE_USERS_PATH);
	User existingUser("existingUsername", "password");
	std::vector<std::string> key;
	key.push_back(existingUser.getUsername());
	DB.write(key, existingUser.serialize());
}

void SignUpServiceTest::tearDown(){
	TestFixture::tearDown();

	Database DB(DATABASE_USERS_PATH);
	std::vector<std::string> key;
	key.push_back("existingUsername");
	DB.erase(key);
}

void SignUpServiceTest::testUserShouldSignUp(){

	Json::Value input;
	input[SERVICE_USERNAME] = "username";
	input[SERVICE_PASSWORD] = "password1234ASD";

	Json::Value output = SignUpService::doSignUp(input);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == "");

	Database DB(DATABASE_USERS_PATH);
	std::vector<std::string> key;
	key.push_back("username");
	DB.erase(key);
}

void SignUpServiceTest::testSignUpShouldRegisterUserInDatabase(){

	Json::Value input;
	input[SERVICE_USERNAME] = "username";
	input[SERVICE_PASSWORD] = "password1234ASD";

	Json::Value output = SignUpService::doSignUp(input);

	Database DB(DATABASE_USERS_PATH);
	std::vector<std::string> key;
	key.push_back("username");
	std::string serializedUser = DB.read(key);
	User user(serializedUser);
	CPPUNIT_ASSERT(user.getUsername() == "username");
	CPPUNIT_ASSERT(user.getPassword() == "password1234ASD");
	DB.erase(key);
}

void SignUpServiceTest::testUsernameShouldAlreadyExist(){

	Json::Value input;
	input[SERVICE_USERNAME] = "existingUsername";
	input[SERVICE_PASSWORD] = "password1234ASD";

	Json::Value output = SignUpService::doSignUp(input);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_USERNAMEEXISTS);
}
