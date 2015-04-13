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

void DatabaseTests::should_write_and_read_single_key() {
	Database* db = new Database(pathTest);
	vector<string> key1, key2;
	key1.push_back("key1");
	key2.push_back("key2");
	db->write(key1, "value1");
	db->write(key2, "value2");
	CPPUNIT_ASSERT(db->read(key1) == "value1");
	CPPUNIT_ASSERT(db->read(key2) == "value2");

	db->erase(key1);
	db->erase(key2);
	delete db;
}

void DatabaseTests::should_write_and_read_double_keys() {
	Database* db = new Database(pathTest);
	vector<string> key1, key2;
	key1.push_back("key1");
	key1.push_back("key2");
	key2.push_back("key2");
	key2.push_back("key1");
	db->write(key1, "value1");
	CPPUNIT_ASSERT(db->read(key1) == "value1");
	CPPUNIT_ASSERT(db->read(key2) == "value1");

	db->erase(key1);
	delete db;
}

void DatabaseTests::should_write_and_read_multiple_keys() {
	Database* db = new Database(pathTest);
	vector<string> key1, key2;
	key1.push_back("key1");
	key1.push_back("key2");
	key1.push_back("key3");
	key1.push_back("key4");
	key2.push_back("key2");
	key2.push_back("key3");
	key2.push_back("key4");
	key2.push_back("key1");
	db->write(key1, "value1");
	CPPUNIT_ASSERT(db->read(key1) == "value1");
	CPPUNIT_ASSERT(db->read(key2) == "value1");

	db->erase(key1);
	delete db;
}

void DatabaseTests::should_erase() {
	Database* db = new Database(pathTest);
	vector<string> key1;
	key1.push_back("key1");
	db->write(key1, "value1");
	CPPUNIT_ASSERT(db->read(key1) == "value1");
	db->erase(key1);
	CPPUNIT_ASSERT_THROW(db->read(key1), KeyNotFoundException);
	delete db;
}

void DatabaseTests::should_modify() {
	Database* db = new Database(pathTest);
	vector<string> key1;
	key1.push_back("key1");
	db->write(key1, "value1");
	CPPUNIT_ASSERT(db->read(key1) == "value1");
	db->write(key1, "value2");
	CPPUNIT_ASSERT(db->read(key1) == "value2");

	db->erase(key1);
	delete db;
}

void DatabaseTests::should_persist() {
	Database* db = new Database(pathTest);
	vector<string> key1;
	key1.push_back("key1");
	db->write(key1, "value1");
	CPPUNIT_ASSERT(db->read(key1) == "value1");
	delete db;
	Database* db2 = new Database(pathTest);
	CPPUNIT_ASSERT(db2->read(key1) == "value1");

	db2->erase(key1);
	delete db2;
}

void DatabaseTests::cant_read_without_keys() {
	Database* db = new Database(pathTest);
	vector<string> invalidKey;

	CPPUNIT_ASSERT_THROW(db->read(invalidKey), InvalidKeyException);
	delete db;
}

void DatabaseTests::cant_write_without_keys() {
	Database* db = new Database(pathTest);
	vector<string> invalidKey;

	CPPUNIT_ASSERT_THROW(db->write(invalidKey, "value"), InvalidKeyException);
	delete db;
}

void DatabaseTests::should_not_find_values() {

	Database* db = new Database(pathTest);
	vector<string> key;
	key.push_back("invalidKey");
	CPPUNIT_ASSERT_THROW(db->read(key), KeyNotFoundException);
	delete db;
}
