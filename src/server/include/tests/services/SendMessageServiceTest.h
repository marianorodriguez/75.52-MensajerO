/*
 * SendMessageServiceTest.h
 *
 *  Created on: 10/5/2015
 *      Author: marian
 */

#ifndef TESTS_SERVICES_SENDMESSAGESERVICETEST_H_
#define TESTS_SERVICES_SENDMESSAGESERVICETEST_H_

#include "ServiceTest.h"
#include "../../main/services/SendMessageService.h"

class SendMessageServiceTest: public ServiceTest {

	CPPUNIT_TEST_SUITE(SendMessageServiceTest);
	CPPUNIT_TEST(testGetUri);
	CPPUNIT_TEST(testShouldThrowInvalidUsername);
	CPPUNIT_TEST(testShouldThrowInvalidPassword);
	CPPUNIT_TEST(testShouldAddMessageToExistingChat);
	CPPUNIT_TEST(testShouldCreateNewChat);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual ~SendMessageServiceTest();

	void setUp();
	void tearDown();

	void testGetUri();
	void testShouldThrowInvalidUsername();
	void testShouldThrowInvalidPassword();
	void testShouldAddMessageToExistingChat();
	void testShouldCreateNewChat();
};

#endif /* TESTS_SERVICES_SENDMESSAGESERVICETEST_H_ */
