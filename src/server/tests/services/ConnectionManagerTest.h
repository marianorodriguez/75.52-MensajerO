/*
 * ConnectionManagerTest.h
 *
 *  Created on: 27/4/2015
 *      Author: marian
 */

#ifndef SERVER_TESTS_SERVICES_CONNECTIONMANAGERTEST_H_
#define SERVER_TESTS_SERVICES_CONNECTIONMANAGERTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include "services/ConnectionManager.h"

class ConnectionManagerTest: public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(ConnectionManagerTest);

	//las comento porque tardan mucho tiempo
	// TODO descomentar estas pruebas!!!!

//	CPPUNIT_TEST(testGetConnectedUsers);
//	CPPUNIT_TEST(testAddRecentlyConnectedUser);
//	CPPUNIT_TEST(testUpdateAlreadyConnectedUser);
//	CPPUNIT_TEST(testDisconnectUser);
//	CPPUNIT_TEST(testManageMultipleUsers);
	CPPUNIT_TEST_SUITE_END();

public:

	ConnectionManagerTest();
	virtual ~ConnectionManagerTest();

	void setUp();
	void tearDown();

	void testAddRecentlyConnectedUser();
	void testUpdateAlreadyConnectedUser();
	void testManageMultipleUsers();
	void testDisconnectUser();
	void testGetConnectedUsers();

private:
	ConnectionManager manager;
	std::map<std::string, int>::iterator it;

};

#endif /* SERVER_TESTS_SERVICES_CONNECTIONMANAGERTEST_H_ */
