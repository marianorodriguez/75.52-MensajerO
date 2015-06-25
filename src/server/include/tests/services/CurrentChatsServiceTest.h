/*
 * CurrentChatsServiceTest.h
 *
 *  Created on: 9/5/2015
 *      Author: marian
 */

#ifndef TESTS_SERVICES_CURRENTCHATSSERVICETEST_H_
#define TESTS_SERVICES_CURRENTCHATSSERVICETEST_H_

#include "ServiceTest.h"
#include "../../main/services/CurrentChatsService.h"

class CurrentChatsServiceTest: public ServiceTest {

	CPPUNIT_TEST_SUITE(CurrentChatsServiceTest);
	CPPUNIT_TEST(testShouldGetUri);
	CPPUNIT_TEST(testShouldGetCurrentChats);
	CPPUNIT_TEST(testShouldThrowInvalidPassword);
	CPPUNIT_TEST(testShouldThrowInvalidUsername);
	CPPUNIT_TEST(shouldGetEmptyChatList);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual ~CurrentChatsServiceTest();

	void setUp();
	void tearDown();

	void testShouldGetUri();
	void testShouldGetCurrentChats();
	void shouldGetEmptyChatList();
	void testShouldThrowInvalidUsername();
	void testShouldThrowInvalidPassword();
};

#endif /* TESTS_SERVICES_CURRENTCHATSSERVICETEST_H_ */
