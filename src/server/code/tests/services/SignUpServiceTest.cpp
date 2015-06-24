/*
 * SignUpServiceTest.cpp
 *
 *  Created on: 9/5/2015
 *      Author: marian
 */

#include "services/SignUpServiceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(SignUpServiceTest);

SignUpServiceTest::~SignUpServiceTest() {
}

void SignUpServiceTest::setUp(){
	ServiceTest::setUp();

	this->service = new SignUpService(*userDB);

	User existingUser("existingUsername", "password");
	std::vector<std::string> key;
	key.push_back(existingUser.getUsername());
	userDB->write(key, existingUser.serialize());
}

void SignUpServiceTest::tearDown(){

	std::vector<std::string> key;
	key.push_back("existingUsername");
	userDB->erase(key);
	ServiceTest::tearDown();
}

void SignUpServiceTest::testUserShouldSignUp(){

	Json::Value input;
	input[SERVICE_USERNAME] = "username";
	input[SERVICE_PASSWORD] = "password1234ASD";

	string output = service->executeRequest(input.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_WHAT].asString() == "");

	std::vector<std::string> key;
	key.push_back("username");
	userDB->erase(key);
}

void SignUpServiceTest::testSignUpShouldRegisterUserInDatabase(){

	Json::Value input;
	input[SERVICE_USERNAME] = "username";
	input[SERVICE_PASSWORD] = "password1234ASD";

	string output = service->executeRequest(input.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	std::vector<std::string> key;
	key.push_back("username");
	std::string serializedUser = userDB->read(key);
	User user(serializedUser);
	CPPUNIT_ASSERT(user.getUsername() == "username");
	CPPUNIT_ASSERT(user.getPassword() == "password1234ASD");
	userDB->erase(key);
}

void SignUpServiceTest::testUsernameShouldAlreadyExist(){

	Json::Value input;
	input[SERVICE_USERNAME] = "existingUsername";
	input[SERVICE_PASSWORD] = "password1234ASD";
	string output = service->executeRequest(input.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_USERNAMEEXISTS);
}
