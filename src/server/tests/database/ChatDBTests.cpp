/*
 * ChatDBTests.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: fran
 */

#include <cppunit/config/SourcePrefix.h>
#include "ChatDBTests.h"
#include "../../main/database/ChatDB.h"
#include <stdio.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ChatDBTests);

string pathTestChat = "src/server/tests/database/testchatdb";

void ChatDBTests::should_read_same_users(){
	ChatDB* db = new ChatDB(pathTestChat);
	bool error = true;
	db->writeChat("user1","user2","value1");
	CPPUNIT_ASSERT(db->readChat("user1","user2",&error) == "value1");
	CPPUNIT_ASSERT(error == false);
	CPPUNIT_ASSERT(db->readChat("user2","user1",&error) == "value1");
	CPPUNIT_ASSERT(error == false);
	delete db;
}
