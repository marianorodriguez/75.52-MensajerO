/*
 * ConnectionManagerTest.h
 *
 *  Created on: 27/4/2015
 *      Author: marian
 */

#ifndef SERVER_TESTS_SERVICES_CONNECTIONMANAGERTEST_H_
#define SERVER_TESTS_SERVICES_CONNECTIONMANAGERTEST_H_

#include "../../main/utilities/ConnectionManager.h"

#include <cppunit/extensions/HelperMacros.h>

class ConnectionManagerTest: public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(ConnectionManagerTest);
	CPPUNIT_TEST(testGetConnectedUsers);
	CPPUNIT_TEST(testAddRecentlyConnectedUser);
	CPPUNIT_TEST(testUpdateAlreadyConnectedUser);
	CPPUNIT_TEST(testDisconnectUser);
	CPPUNIT_TEST(testManageMultipleUsers);
	CPPUNIT_TEST_SUITE_END();

public:
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
	Database* testDb;
	std::map<std::string, int>::iterator it;

};

#endif /* SERVER_TESTS_SERVICES_CONNECTIONMANAGERTEST_H_ */
