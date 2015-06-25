/*
 * BroadcastServiceTest.h
 *
 *  Created on: 14/6/2015
 *      Author: marian
 */

#ifndef INCLUDE_TESTS_SERVICES_BROADCASTSERVICETEST_H_
#define INCLUDE_TESTS_SERVICES_BROADCASTSERVICETEST_H_

#include "../../../include/tests/services/ServiceTest.h"
#include "../../main/services/BroadcastService.h"

class BroadcastServiceTest: public ServiceTest {

	CPPUNIT_TEST_SUITE(BroadcastServiceTest);
	CPPUNIT_TEST(testShouldGetUri);
	CPPUNIT_TEST(testShouldDoBroadcast);
	CPPUNIT_TEST(testShouldBeInvalidPassword);
	CPPUNIT_TEST(testShouldBeInvalidUsername);
	CPPUNIT_TEST_SUITE_END();

public:

	void setUp();
	void tearDown();

	virtual ~BroadcastServiceTest();

	void testShouldGetUri();
	void testShouldDoBroadcast();
	void testShouldBeInvalidPassword();
	void testShouldBeInvalidUsername();

};

#endif /* INCLUDE_TESTS_SERVICES_BROADCASTSERVICETEST_H_ */
