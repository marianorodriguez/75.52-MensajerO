/*
 * SomethingForMeServiceTest.h
 *
 *  Created on: 9/5/2015
 *      Author: marian
 */

#ifndef TESTS_SERVICES_SOMETHINGFORMESERVICETEST_H_
#define TESTS_SERVICES_SOMETHINGFORMESERVICETEST_H_

#include "ServiceTest.h"
#include "../../main/services/SomethingForMeService.h"

class SomethingForMeServiceTest: public ServiceTest{

	CPPUNIT_TEST_SUITE(SomethingForMeServiceTest);
	CPPUNIT_TEST(testGetUri);
	CPPUNIT_TEST(shouldThrowInvalidPassword);
	CPPUNIT_TEST(shouldThrowInvalidUsername);
	CPPUNIT_TEST(testGetNewMessages);
	CPPUNIT_TEST(testDoubleRequestShouldReturnNoMessages);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual ~SomethingForMeServiceTest();

	void setUp();
	void tearDown();

	void testGetUri();
	void shouldThrowInvalidUsername();
	void shouldThrowInvalidPassword();
	void testGetNewMessages();
	void testDoubleRequestShouldReturnNoMessages();
};

#endif /* TESTS_SERVICES_SOMETHINGFORMESERVICETEST_H_ */
