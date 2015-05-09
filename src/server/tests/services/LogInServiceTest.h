/*
 * LogInServiceTest.h
 *
 *  Created on: 9/5/2015
 *      Author: marian
 */

#ifndef SERVER_TESTS_SERVICES_LOGINSERVICETEST_H_
#define SERVER_TESTS_SERVICES_LOGINSERVICETEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include "services/LogInService.h"

class LogInServiceTest: public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(LogInServiceTest);
	CPPUNIT_TEST(testLogIn);
	CPPUNIT_TEST(testShouldThrowInvalidUsername);
	CPPUNIT_TEST(testShouldThrowInvalidPassword);
	CPPUNIT_TEST_SUITE_END();

public:
	LogInServiceTest();
	virtual ~LogInServiceTest();

	void setUp();
	void tearDown();

	void testLogIn();
	void testShouldThrowInvalidUsername();
	void testShouldThrowInvalidPassword();

};

#endif /* SERVER_TESTS_SERVICES_LOGINSERVICETEST_H_ */
