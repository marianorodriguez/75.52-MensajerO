/*
 * ServicesIntegrationTests.cpp
 *
 *  Created on: 18/4/2015
 *      Author: marian
 */

#include "ServicesIntegrationTests.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ServicesIntegrationTests);

void ServicesIntegrationTests::setUp() {
	CppUnit::TestFixture::setUp();

	this->testClient = new RestClient();

	this->testServer = new ServerThread();
	testServer->run();
}

void ServicesIntegrationTests::tearDown() {
	CppUnit::TestFixture::tearDown();

	delete this->testClient;

	this->testServer->shutdown();
	this->testServer->join();
	delete this->testServer;
}

void ServicesIntegrationTests::signUp_should_register_new_user() {

	RestQuery query;
	query.setBaseUri("127.0.0.1:8081/" + SERVICE_SIGNUP_NAME);

	Json::Value sendUser;
	sendUser[SERVICE_SIGNUP_NAME][SERVICE_USERNAME] = "newUser";
	sendUser[SERVICE_SIGNUP_NAME][SERVICE_PASSWORD] = "md5_hashed_pwd";
	query.setPostData(sendUser.toStyledString());

	std::string response = testClient->execute(RestClient::POST, query);

	Json::Value responseUser(response);

	CPPUNIT_ASSERT(!response.empty());
	CPPUNIT_ASSERT(
			responseUser[JSON_USER_ROOT][JSON_USER_NAME].asString() == "newUser");
	CPPUNIT_ASSERT(
			responseUser[JSON_USER_ROOT][JSON_USER_LOCATION].asString() == DEFAULT_USER_LOCATION);
	CPPUNIT_ASSERT(
			responseUser[JSON_USER_ROOT][JSON_USER_LOCATION].asString() == DEFAULT_USER_STATUS);
	CPPUNIT_ASSERT(
			responseUser[JSON_USER_ROOT][JSON_USER_PROFILE_PICTURE].asString() == DEFAULT_USER_PROFILE_PICTURE);

}

void ServicesIntegrationTests::signUp_username_should_already_exist() {

	Database* DB = new Database();

	std::vector<std::string> key;
	std::string username = "username_test";
	std::string password = "password_test";
	key.push_back(username);
	DB->write(key, "username_value");

	RestQuery query;
	query.setBaseUri("127.0.0.1:8081/" + SERVICE_SIGNUP_NAME);

	Json::Value sendUser;
	sendUser[SERVICE_SIGNUP_NAME][SERVICE_USERNAME] = username;
	sendUser[SERVICE_SIGNUP_NAME][SERVICE_PASSWORD] = password;
	query.setPostData(sendUser.toStyledString());

	std::string response = testClient->execute(RestClient::POST, query);

	//TODO ver de donde puedo obtener el status para hacer assertEquals(status , 404);
	CPPUNIT_ASSERT(false);
}
