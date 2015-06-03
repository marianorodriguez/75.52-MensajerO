/*
 * LogInServiceTest.cpp
 *
 *  Created on: 9/5/2015
 *      Author: marian
 */

#include "services/LogInServiceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(LogInServiceTest);

LogInServiceTest::LogInServiceTest() {
}

LogInServiceTest::~LogInServiceTest() {
}

void LogInServiceTest::setUp() {
	TestFixture::setUp();

	Database DB(DATABASE_USERS_PATH);
	User validUser("username_1", "password");
	std::vector<std::string> key;
	key.push_back(validUser.getUsername());
	DB.write(key, validUser.serialize());
}

void LogInServiceTest::tearDown() {
	TestFixture::tearDown();

	Database DB(DATABASE_USERS_PATH);
	std::vector<std::string> key;
	key.push_back("username_1");
	DB.erase(key);
}

void LogInServiceTest::testLogIn() {

	Json::Value input;
	input[SERVICE_USERNAME] = "username_1";
	input[SERVICE_PASSWORD] = "password";

	Json::Value output = LogInService::doLogIn(input);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == "");
}

void LogInServiceTest::testShouldThrowInvalidPassword() {
	Json::Value input;
	input[SERVICE_USERNAME] = "username_1";
	input[SERVICE_PASSWORD] = "invalid_password";

	Json::Value output = LogInService::doLogIn(input);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(
			output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDPWD);
}

void LogInServiceTest::testShouldThrowInvalidUsername() {
	Json::Value input;
	input[SERVICE_USERNAME] = "unexistant_username";
	input[SERVICE_PASSWORD] = "password";

	Json::Value output = LogInService::doLogIn(input);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(
			output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDUSER);
}

