/*
 * ServicesIntegrationTests.h
 *
 *  Created on: 18/4/2015
 *      Author: marian
 */

#ifndef SERVER_TESTS_SERVICES_SERVICESINTEGRATIONTESTS_H_
#define SERVER_TESTS_SERVICES_SERVICESINTEGRATIONTESTS_H_
#include "cppunit/extensions/HelperMacros.h"
#include "../rest-client/RestClient.h"
#include "services/ServerThread.h"
#include "database/Database.h"
#include "json.h"
#include "config.h"

class ServicesIntegrationTests: public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(ServicesIntegrationTests);
	CPPUNIT_TEST(signUp_should_register_new_user);
	CPPUNIT_TEST(signUp_username_should_already_exist);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	//SIGN UP SERVICE
	void signUp_should_register_new_user();
	void signUp_username_should_already_exist();

private:
	RestClient* testClient;
	ServerThread* testServer;
};

#endif /* SERVER_TESTS_SERVICES_SERVICESINTEGRATIONTESTS_H_ */
