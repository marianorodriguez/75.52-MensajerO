/*
 * ConnectionManagerTest.h
 *
 *  Created on: 27/4/2015
 *      Author: marian
 */

#ifndef SERVER_TESTS_SERVICES_CONNECTIONMANAGERTEST_H_
#define SERVER_TESTS_SERVICES_CONNECTIONMANAGERTEST_H_

#include "ServiceTest.h"
#include "../../main/services/DeleteChatService.h"

class DeleteChatServiceTest: public ServiceTest{

	CPPUNIT_TEST_SUITE(DeleteChatServiceTest);
	CPPUNIT_TEST(testShouldGetUri);
	CPPUNIT_TEST(testDeleteChat);
	CPPUNIT_TEST(testShouldBeInvalidPassword);
	CPPUNIT_TEST(testShouldBeInvalidUsername);
	CPPUNIT_TEST_SUITE_END();

public:

	virtual ~DeleteChatServiceTest();

	void setUp();
	void tearDown();

	void testShouldGetUri();
	void testShouldBeInvalidPassword();
	void testShouldBeInvalidUsername();
	void testDeleteChat();
};

#endif /* SERVER_TESTS_SERVICES_CONNECTIONMANAGERTEST_H_ */
