/*
 * BroadcastServiceTest.h
 *
 *  Created on: 14/6/2015
 *      Author: marian
 */

#ifndef INCLUDE_TESTS_SERVICES_BROADCASTSERVICETEST_H_
#define INCLUDE_TESTS_SERVICES_BROADCASTSERVICETEST_H_

#include "../../main/services/BroadcastService.h"
#include <cppunit/extensions/HelperMacros.h>

class BroadcastServiceTest: public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(BroadcastServiceTest);
	CPPUNIT_TEST(testShouldDoBroadcast);
	CPPUNIT_TEST(testShouldNotSendBroadcastToOfflineUsers);
	CPPUNIT_TEST(testShouldBeInvalidPassword);
	CPPUNIT_TEST(testShouldBeInvalidUsername);
	CPPUNIT_TEST_SUITE_END();


public:

	void setUp();
	void tearDown();
	BroadcastServiceTest();
	virtual ~BroadcastServiceTest();

	void testShouldDoBroadcast();
	void testShouldNotSendBroadcastToOfflineUsers();
	void testShouldBeInvalidPassword();
	void testShouldBeInvalidUsername();

};

#endif /* INCLUDE_TESTS_SERVICES_BROADCASTSERVICETEST_H_ */
