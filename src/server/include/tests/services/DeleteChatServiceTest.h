/*
 * ConnectionManagerTest.h
 *
 *  Created on: 27/4/2015
 *      Author: marian
 */

#ifndef SERVER_TESTS_SERVICES_CONNECTIONMANAGERTEST_H_
#define SERVER_TESTS_SERVICES_CONNECTIONMANAGERTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include "../../main/services/DeleteChatService.h"

class DeleteChatServiceTest: public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(DeleteChatServiceTest);
	CPPUNIT_TEST(testDeleteChat);
	CPPUNIT_TEST(testLoggedOutUser);
	CPPUNIT_TEST_SUITE_END();

public:

	DeleteChatServiceTest();
	virtual ~DeleteChatServiceTest();

	void setUp();
	void tearDown();
	void testLoggedOutUser();
	void testDeleteChat();
};

#endif /* SERVER_TESTS_SERVICES_CONNECTIONMANAGERTEST_H_ */
