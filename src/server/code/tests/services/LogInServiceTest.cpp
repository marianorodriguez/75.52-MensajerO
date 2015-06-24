/*
 * LogInServiceTest.cpp
 *
 *  Created on: 9/5/2015
 *      Author: marian
 */

#include "services/LogInServiceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(LogInServiceTest);

LogInServiceTest::~LogInServiceTest() {
}

void LogInServiceTest::setUp() {
	ServiceTest::setUp();

	this->service = new LogInService(*userDB);

	User validUser("username_1", "password");
	std::vector<std::string> key;
	key.push_back(validUser.getUsername());
	userDB->write(key, validUser.serialize());
}

void LogInServiceTest::tearDown() {

	std::vector<std::string> key;
	key.push_back("username_1");
	userDB->erase(key);
	LocationManager::destroyInstance();
	ServiceTest::tearDown();
}

void LogInServiceTest::testLogIn() {

	Json::Value input;
	input[SERVICE_USERNAME] = "username_1";
	input[SERVICE_PASSWORD] = "password";

	string output = service->executeRequest(input.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_WHAT].asString() == "");
}

void LogInServiceTest::testShouldThrowInvalidPassword() {

	Json::Value input;
	input[SERVICE_USERNAME] = "username_1";
	input[SERVICE_PASSWORD] = "invalid_password";

	string output = service->executeRequest(input.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(
			jsonOut[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDPWD);
}

void LogInServiceTest::testShouldThrowInvalidUsername() {

	Json::Value input;
	input[SERVICE_USERNAME] = "unexistant_username";
	input[SERVICE_PASSWORD] = "password";

	string output = service->executeRequest(input.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(
			jsonOut[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDUSER);
}

