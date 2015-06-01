/*
 * UserConfigServiceTest.h
 *
 *  Created on: 9/5/2015
 *      Author: marian
 */

#ifndef TESTS_SERVICES_USERCONFIGSERVICETEST_H_
#define TESTS_SERVICES_USERCONFIGSERVICETEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include "../../main/services/UserConfigService.h"

class UserConfigServiceTest: public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(UserConfigServiceTest);
	CPPUNIT_TEST(testUserShouldConfigureProfile);
	CPPUNIT_TEST(testUsernameShouldNotExist);
	CPPUNIT_TEST(testShouldBeInvalidPassword);
	CPPUNIT_TEST_SUITE_END();
public:
	UserConfigServiceTest();
	virtual ~UserConfigServiceTest();

	void setUp();
	void tearDown();

	void testUserShouldConfigureProfile();
	void testShouldBeInvalidPassword();
	void testUsernameShouldNotExist();
};

#endif /* TESTS_SERVICES_USERCONFIGSERVICETEST_H_ */
