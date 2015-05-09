/*
 * SignUpServiceTest.h
 *
 *  Created on: 9/5/2015
 *      Author: marian
 */

#ifndef TESTS_SERVICES_SIGNUPSERVICETEST_H_
#define TESTS_SERVICES_SIGNUPSERVICETEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include "services/SignUpService.h"

class SignUpServiceTest: public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(SignUpServiceTest);
	CPPUNIT_TEST(testUserShouldSignUp);
	CPPUNIT_TEST(testSignUpShouldRegisterUserInDatabase);
	CPPUNIT_TEST(testUsernameShouldAlreadyExist);
	CPPUNIT_TEST_SUITE_END();
public:
	SignUpServiceTest();
	virtual ~SignUpServiceTest();

	void setUp();
	void tearDown();

	void testUserShouldSignUp();
	void testSignUpShouldRegisterUserInDatabase();
	void testUsernameShouldAlreadyExist();


};

#endif /* TESTS_SERVICES_SIGNUPSERVICETEST_H_ */
