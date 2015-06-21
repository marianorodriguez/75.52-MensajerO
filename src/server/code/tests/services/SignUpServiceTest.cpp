/*
 * SignUpServiceTest.cpp
 *
 *  Created on: 9/5/2015
 *      Author: marian
 */

#include "services/SignUpServiceTest.h"

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
	DB.close();
}

void SignUpServiceTest::tearDown(){
	TestFixture::tearDown();

	Database DB(DATABASE_USERS_PATH);
	std::vector<std::string> key;
	key.push_back("existingUsername");
	DB.erase(key);
	DB.close();
}

void SignUpServiceTest::testUserShouldSignUp(){
	Database usersDb(DATABASE_USERS_PATH);
	SignUpService signUpService(usersDb);

	Json::Value input;
	input[SERVICE_USERNAME] = "username";
	input[SERVICE_PASSWORD] = "password1234ASD";

	Json::Value output = signUpService.doSignUp(input);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == "");

	std::vector<std::string> key;
	key.push_back("username");
	usersDb.erase(key);
}

void SignUpServiceTest::testSignUpShouldRegisterUserInDatabase(){
	Database usersDb(DATABASE_USERS_PATH);
	SignUpService signUpService(usersDb);

	Json::Value input;
	input[SERVICE_USERNAME] = "username";
	input[SERVICE_PASSWORD] = "password1234ASD";

	Json::Value output = signUpService.doSignUp(input);

	std::vector<std::string> key;
	key.push_back("username");
	std::string serializedUser = usersDb.read(key);
	User user(serializedUser);
	CPPUNIT_ASSERT(user.getUsername() == "username");
	CPPUNIT_ASSERT(user.getPassword() == "password1234ASD");
	usersDb.erase(key);
}

void SignUpServiceTest::testUsernameShouldAlreadyExist(){
	Database usersDb(DATABASE_USERS_PATH);
	SignUpService signUpService(usersDb);
	
	Json::Value input;
	input[SERVICE_USERNAME] = "existingUsername";
	input[SERVICE_PASSWORD] = "password1234ASD";

	Json::Value output = signUpService.doSignUp(input);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_USERNAMEEXISTS);
}
