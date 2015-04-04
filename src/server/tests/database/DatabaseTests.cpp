/*
 * DatabaseTests.cpp
 *
 *  Created on: Mar 31, 2015
 *      Author: fran
 */

#include <cppunit/config/SourcePrefix.h>
#include "DatabaseTests.h"
#include "../../main/database/Database.h"
#include <stdio.h>

CPPUNIT_TEST_SUITE_REGISTRATION(DatabaseTests);

string pathTest = "src/server/tests/database/testdb";

void DatabaseTests::should_write_and_read() {
	Database* db = new Database(pathTest);
	db->write("key1","value1");
	db->write("key2","value2");
	bool error = true;
	CPPUNIT_ASSERT(db->read("key1",&error) == "value1");
	CPPUNIT_ASSERT(db->read("key2",&error) == "value2");
	CPPUNIT_ASSERT(error == false);
	delete db;
}

void DatabaseTests::should_erase(){
	Database* db = new Database(pathTest);
	bool error = true;
	CPPUNIT_ASSERT(db->read("key2",&error) == "value2");
	db->write("key1","value1");
	CPPUNIT_ASSERT(db->read("key1",&error) == "value1");
	CPPUNIT_ASSERT(error == false);
	db->erase("key1");
	db->read("key1",&error);
	CPPUNIT_ASSERT(error == true);
	delete db;
}

void DatabaseTests::should_modify(){
	Database* db = new Database(pathTest);
	bool error = false;
	db->write("key1","value1");
	CPPUNIT_ASSERT(db->read("key1",&error) == "value1");
	db->write("key1","value2");
	CPPUNIT_ASSERT(db->read("key1",&error) == "value2");
	delete db;
}

void DatabaseTests::should_persist() {
	Database* db = new Database(pathTest);
	bool error = false;
	db->write("key1","value1");
	CPPUNIT_ASSERT(db->read("key1",&error) == "value1");
	delete db;
	Database* db2 = new Database(pathTest);
	CPPUNIT_ASSERT(db2->read("key1",&error) == "value1");
	delete db2;
}

