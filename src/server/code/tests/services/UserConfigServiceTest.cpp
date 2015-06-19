/*
 * UserConfigServiceTest.cpp
 *
 *  Created on: 9/5/2015
 *      Author: marian
 */

#include "services/UserConfigServiceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(UserConfigServiceTest);

UserConfigServiceTest::UserConfigServiceTest() {
}

UserConfigServiceTest::~UserConfigServiceTest() {
}

void UserConfigServiceTest::setUp() {
	CppUnit::TestFixture::setUp();
	Database DB(DATABASE_USERS_PATH);

	User user("username_config", "password");
	std::vector<std::string> key;
	key.push_back(user.getUsername());
	DB.write(key, user.serialize());
	DB.close();
}

void UserConfigServiceTest::tearDown() {
	CppUnit::TestFixture::tearDown();

	Database DB(DATABASE_USERS_PATH);
	std::vector<std::string> key;
	key.push_back("username_config");
	DB.erase(key);
	DB.close();
}

void UserConfigServiceTest::testUserShouldConfigureProfile() {

	Database* DB = new Database(DATABASE_USERS_PATH);
	std::vector<std::string> key;
	key.push_back("username_config");
	User user(DB->read(key));

	//verifico que el user tenga los valores por default
	CPPUNIT_ASSERT(user.getLocation() == DEFAULT_USER_LOCATION);
	CPPUNIT_ASSERT(user.getStatus() == DEFAULT_USER_STATUS);
	CPPUNIT_ASSERT(
			user.getProfilePicture() == DEFAULT_USER_PROFILE_PICTURE);

	DB->close();

	Json::Value data;
	data[SERVICE_USERNAME] = "username_config";
	data[SERVICE_PASSWORD] = "password";
	data[SERVICE_USERCONFIG_LOCATION] = "(0,5)";
	data[SERVICE_USERCONFIG_STATUS] = "new Status";
	data[SERVICE_USERCONFIG_PICTURE] = "new profile picture";

	Json::Value output = UserConfigService::doUserConfig(data);

	Database* newDB = new Database(DATABASE_USERS_PATH);
	User modifiedUser(newDB->read(key));
	newDB->close();

	CPPUNIT_ASSERT(modifiedUser.getLocation() == "CABA");
	CPPUNIT_ASSERT(modifiedUser.getStatus() == "new Status");
	CPPUNIT_ASSERT(
			modifiedUser.getProfilePicture() == "new profile picture");

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == "");
}

void UserConfigServiceTest::testShouldBeInvalidPassword() {

	Json::Value data;
	data[SERVICE_USERNAME] = "username_config";
	data[SERVICE_PASSWORD] = "invalidPassword";
	data[SERVICE_USERCONFIG_LOCATION] = "new Location";
	data[SERVICE_USERCONFIG_STATUS] = "new Status";
	data[SERVICE_USERCONFIG_PICTURE] = "new profile picture";

	Json::Value output = UserConfigService::doUserConfig(data);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(
			output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDPWD);
}

void UserConfigServiceTest::testUsernameShouldNotExist() {

	Json::Value data;
	data[SERVICE_USERNAME] = "non-existant-user";
	data[SERVICE_PASSWORD] = "password";
	data[SERVICE_USERCONFIG_LOCATION] = "new Location";
	data[SERVICE_USERCONFIG_STATUS] = "new Status";
	data[SERVICE_USERCONFIG_PICTURE] = "new profile picture";

	Json::Value output = UserConfigService::doUserConfig(data);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(
			output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_INVALIDUSER);
}
