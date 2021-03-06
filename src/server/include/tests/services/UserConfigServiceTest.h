/*
 * UserConfigServiceTest.h
 *
 *  Created on: 9/5/2015
 *      Author: marian
 */

#ifndef TESTS_SERVICES_USERCONFIGSERVICETEST_H_
#define TESTS_SERVICES_USERCONFIGSERVICETEST_H_

#include "ServiceTest.h"
#include "../../main/services/UserConfigService.h"

class UserConfigServiceTest: public ServiceTest {

	CPPUNIT_TEST_SUITE(UserConfigServiceTest);
	CPPUNIT_TEST(testGetUri);
	CPPUNIT_TEST(testUserShouldConfigureProfile);
	CPPUNIT_TEST(testUsernameShouldNotExist);
	CPPUNIT_TEST(testShouldBeInvalidPassword);
	CPPUNIT_TEST_SUITE_END();
public:
	virtual ~UserConfigServiceTest();

	void setUp();
	void tearDown();

	void testGetUri();
	void testUserShouldConfigureProfile();
	void testShouldBeInvalidPassword();
	void testUsernameShouldNotExist();
};

#endif /* TESTS_SERVICES_USERCONFIGSERVICETEST_H_ */
