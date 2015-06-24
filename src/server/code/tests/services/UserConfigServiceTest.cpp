/*
 * UserConfigServiceTest.cpp
 *
 *  Created on: 9/5/2015
 *      Author: marian
 */

#include "services/UserConfigServiceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(UserConfigServiceTest);

UserConfigServiceTest::~UserConfigServiceTest() {
}

void UserConfigServiceTest::setUp() {
	ServiceTest::setUp();

	this->service = new UserConfigService(*userDB);

	User user("username_config", "password");
	std::vector<std::string> key;
	key.push_back(user.getUsername());
	userDB->write(key, user.serialize());
}

void UserConfigServiceTest::tearDown() {

	std::vector<std::string> key;
	key.push_back("username_config");
	userDB->erase(key);

	ServiceTest::tearDown();
}

void UserConfigServiceTest::testUserShouldConfigureProfile() {

	std::vector<std::string> key;
	key.push_back("username_config");
	User user(userDB->read(key));

	//verifico que el user tenga los valores por default
	CPPUNIT_ASSERT(user.getLocation() == DEFAULT_USER_LOCATION);
	CPPUNIT_ASSERT(user.getStatus() == DEFAULT_USER_STATUS);
	CPPUNIT_ASSERT(
			user.getProfilePicture() == DEFAULT_USER_PROFILE_PICTURE);

	Json::Value data;
	data[SERVICE_USERNAME] = "username_config";
	data[SERVICE_PASSWORD] = "password";
	data[SERVICE_USERCONFIG_LOCATION] = "(0,5)";
	data[SERVICE_USERCONFIG_STATUS] = "new Status";
	data[SERVICE_USERCONFIG_PICTURE] = "new profile picture";

	string output = service->executeRequest(data.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);


	User modifiedUser(userDB->read(key));

	CPPUNIT_ASSERT(modifiedUser.getLocation() == "CABA");
	CPPUNIT_ASSERT(modifiedUser.getStatus() == "new Status");
	CPPUNIT_ASSERT(
			modifiedUser.getProfilePicture() == "new profile picture");

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_WHAT].asString() == "");
}

void UserConfigServiceTest::testShouldBeInvalidPassword() {

	Json::Value data;
	data[SERVICE_USERNAME] = "username_config";
	data[SERVICE_PASSWORD] = "invalidPassword";
	data[SERVICE_USERCONFIG_LOCATION] = "new Location";
	data[SERVICE_USERCONFIG_STATUS] = "new Status";
	data[SERVICE_USERCONFIG_PICTURE] = "new profile picture";

	string output = service->executeRequest(data.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(
			jsonOut[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDPWD);
}

void UserConfigServiceTest::testUsernameShouldNotExist() {

	Json::Value data;
	data[SERVICE_USERNAME] = "non-existant-user";
	data[SERVICE_PASSWORD] = "password";
	data[SERVICE_USERCONFIG_LOCATION] = "new Location";
	data[SERVICE_USERCONFIG_STATUS] = "new Status";
	data[SERVICE_USERCONFIG_PICTURE] = "new profile picture";

	string output = service->executeRequest(data.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(
			jsonOut[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDUSER);
}
