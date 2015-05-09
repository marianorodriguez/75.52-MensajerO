/*
 * CurrentChatsServiceTest.h
 *
 *  Created on: 9/5/2015
 *      Author: marian
 */

#ifndef TESTS_SERVICES_CURRENTCHATSSERVICETEST_H_
#define TESTS_SERVICES_CURRENTCHATSSERVICETEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include "services/CurrentChatsService.h"

class CurrentChatsServiceTest: public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(CurrentChatsServiceTest);
	CPPUNIT_TEST(testShouldGetCurrentChats);
	CPPUNIT_TEST(testShouldThrowInvalidPassword);
	CPPUNIT_TEST(testShouldThrowInvalidUsername);
	CPPUNIT_TEST(shouldGetEmptyChatList);
	CPPUNIT_TEST_SUITE_END();

public:
	CurrentChatsServiceTest();
	virtual ~CurrentChatsServiceTest();

	void setUp();
	void tearDown();

	void testShouldGetCurrentChats();
	void shouldGetEmptyChatList();
	void testShouldThrowInvalidUsername();
	void testShouldThrowInvalidPassword();
};

#endif /* TESTS_SERVICES_CURRENTCHATSSERVICETEST_H_ */
