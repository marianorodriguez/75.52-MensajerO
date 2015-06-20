/*
 * UsersServiceTest.h
 *
 *  Created on: 10/5/2015
 *      Author: marian
 */

#ifndef TESTS_SERVICES_USERSSERVICETEST_H_
#define TESTS_SERVICES_USERSSERVICETEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include "../../main/services/UsersService.h"

class UsersServiceTest: public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(UsersServiceTest);
	CPPUNIT_TEST(testLoggedOutUser);
	CPPUNIT_TEST(testShouldReturnAllUsersInDB);
	CPPUNIT_TEST(testShouldThrowInvalidPassword);
	CPPUNIT_TEST(testShouldThrowInvalidUsername);
	CPPUNIT_TEST_SUITE_END();

public:
	UsersServiceTest();
	virtual ~UsersServiceTest();

	void setUp();
	void tearDown();

	void testLoggedOutUser();
	void testShouldReturnAllUsersInDB();
	void testShouldThrowInvalidPassword();
	void testShouldThrowInvalidUsername();
};

#endif /* TESTS_SERVICES_USERSSERVICETEST_H_ */
