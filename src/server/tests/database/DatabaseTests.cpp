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
	Database db(pathTest);
	vector<string> key1, key2;
	key1.push_back("key1");
	key2.push_back("key2");
	db.write(key1, "value1");
	db.write(key2, "value2");
	CPPUNIT_ASSERT(db.read(key1) == "value1");
	CPPUNIT_ASSERT(db.read(key2) == "value2");

	db.erase(key1);
	db.erase(key2);
	
}

void DatabaseTests::should_write_and_read_double_keys() {
	Database db(pathTest);
	vector<string> key1, key2;
	key1.push_back("key1");
	key1.push_back("key2");
	key2.push_back("key2");
	key2.push_back("key1");
	db.write(key1, "value1");
	CPPUNIT_ASSERT(db.read(key1) == "value1");
	CPPUNIT_ASSERT(db.read(key2) == "value1");

	db.erase(key1);
	
}

void DatabaseTests::should_write_and_read_multiple_keys() {
	Database db(pathTest);
	vector<string> key1, key2;
	key1.push_back("key1");
	key1.push_back("key2");
	key1.push_back("key3");
	key1.push_back("key4");
	key2.push_back("key2");
	key2.push_back("key3");
	key2.push_back("key4");
	key2.push_back("key1");
	db.write(key1, "value1");
	CPPUNIT_ASSERT(db.read(key1) == "value1");
	CPPUNIT_ASSERT(db.read(key2) == "value1");

	db.erase(key1);
	
}

void DatabaseTests::should_erase() {
	Database db(pathTest);
	vector<string> key1;
	key1.push_back("key1");
	db.write(key1, "value1");
	CPPUNIT_ASSERT(db.read(key1) == "value1");
	db.erase(key1);
	CPPUNIT_ASSERT_THROW(db.read(key1), KeyNotFoundException);
	
}

void DatabaseTests::should_modify() {
	Database db(pathTest);
	vector<string> key1;
	key1.push_back("key1");
	db.write(key1, "value1");
	CPPUNIT_ASSERT(db.read(key1) == "value1");
	db.write(key1, "value2");
	CPPUNIT_ASSERT(db.read(key1) == "value2");

	db.close();

	Database db2(pathTest);
	CPPUNIT_ASSERT(db2.read(key1) == "value2");

	db2.erase(key1);
}

void DatabaseTests::should_persist() {
	Database db(pathTest);
	vector<string> key1;
	key1.push_back("key1");
	db.write(key1, "value1");
	CPPUNIT_ASSERT(db.read(key1) == "value1");
	
	db.close();
	
	Database db2(pathTest);
	CPPUNIT_ASSERT(db2.read(key1) == "value1");

	db2.erase(key1);
}

void DatabaseTests::cant_read_without_keys() {
	Database db(pathTest);
	vector<string> invalidKey;

	CPPUNIT_ASSERT_THROW(db.read(invalidKey), InvalidKeyException);
	
}

void DatabaseTests::cant_write_without_keys() {
	Database db(pathTest);
	vector<string> invalidKey;

	CPPUNIT_ASSERT_THROW(db.write(invalidKey, "value"), InvalidKeyException);
}

void DatabaseTests::should_not_find_values() {

	Database db(pathTest);
	vector<string> key;
	key.push_back("invalidKey");
	CPPUNIT_ASSERT_THROW(db.read(key), KeyNotFoundException);
}

void DatabaseTests::cant_use_invalid_key(){

	Database db(pathTest);
	vector<string> key1;
	key1.push_back("");
	CPPUNIT_ASSERT_THROW_MESSAGE("Can't have empty key", 
						db.write(key1, "value"), InvalidKeyException);

	vector<string> key2;
	key2.push_back("validUsername");
	key2.push_back("#$cantHave/Invalid%Characters");
	CPPUNIT_ASSERT_THROW_MESSAGE("Can't have invalid characters", 
						db.write(key2, "value"), InvalidKeyException);

	vector<string> key3;
	key3.push_back("   ");
	key3.push_back("cantHaveOnlySpaces");
	CPPUNIT_ASSERT_THROW(db.write(key3, "value"), InvalidKeyException);

	vector<string> key4;
	key4.push_back(" cantStartWithSpaces");
	CPPUNIT_ASSERT_THROW(db.write(key4, "value"), InvalidKeyException);

	vector<string> key5;
	key5.push_back("cantEndWithSpaces  ");
	CPPUNIT_ASSERT_THROW(db.write(key5, "value"), InvalidKeyException);
}
