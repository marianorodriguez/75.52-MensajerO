/*
 * SomethingForMeServiceTest.h
 *
 *  Created on: 9/5/2015
 *      Author: marian
 */

#ifndef TESTS_SERVICES_SOMETHINGFORMESERVICETEST_H_
#define TESTS_SERVICES_SOMETHINGFORMESERVICETEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include "../../main/services/SomethingForMeService.h"

class SomethingForMeServiceTest: public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(SomethingForMeServiceTest);
	CPPUNIT_TEST(shouldThrowInvalidPassword);
	CPPUNIT_TEST(shouldThrowInvalidUsername);
	CPPUNIT_TEST(testGetNewMessages);
	CPPUNIT_TEST(testDoubleRequestShouldReturnNoMessages);
	CPPUNIT_TEST_SUITE_END();

public:
	SomethingForMeServiceTest();
	virtual ~SomethingForMeServiceTest();

	void setUp();
	void tearDown();

	void shouldThrowInvalidUsername();
	void shouldThrowInvalidPassword();
	void testGetNewMessages();
	void testDoubleRequestShouldReturnNoMessages();
};

#endif /* TESTS_SERVICES_SOMETHINGFORMESERVICETEST_H_ */
