/*
 * DatabaseTests.cpp
 *
 *  Created on: Mar 31, 2015
 *      Author: fran
 */

#include <cppunit/config/SourcePrefix.h>
#include "../../include/tests/database/DatabaseTests.h"
#include "../../include/main/database/Database.h"
#include <stdio.h>

CPPUNIT_TEST_SUITE_REGISTRATION(DatabaseTests);

string pathTest = "database/test/testdb";

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
	db.close();

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
	db.close();
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
	db.close();
}

void DatabaseTests::should_erase() {
	Database db(pathTest);
	vector<string> key1;
	key1.push_back("key1");
	db.write(key1, "value1");
	CPPUNIT_ASSERT(db.read(key1) == "value1");
	db.erase(key1);
	CPPUNIT_ASSERT_THROW(db.read(key1), KeyNotFoundException);
	db.close();

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
	db2.close();
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
	db2.close();
}

void DatabaseTests::cant_read_without_keys() {
	Database db(pathTest);
	vector<string> invalidKey;

	CPPUNIT_ASSERT_THROW(db.read(invalidKey), InvalidKeyException);
	db.close();

}

void DatabaseTests::cant_write_without_keys() {
	Database db(pathTest);
	vector<string> invalidKey;

	CPPUNIT_ASSERT_THROW(db.write(invalidKey, "value"), InvalidKeyException);
	db.close();

}

void DatabaseTests::should_not_find_values() {
	Database db(pathTest);
	vector<string> key;
	key.push_back("invalidKey");
	CPPUNIT_ASSERT_THROW(db.read(key), KeyNotFoundException);
	db.close();

}

void DatabaseTests::should_return_all_keys_in_db() {

	Database db(pathTest);
	vector<string> key1;
	vector<string> key2;
	vector<string> key3;
	vector<string> key4;

	key1.push_back("user_1");
	key2.push_back("user_2");
	key3.push_back("user_3");
	key4.push_back("user_4");

	db.write(key1, "value1");
	db.write(key2, "value2");
	db.write(key3, "value3");
	db.write(key4, "value4");

	vector<string> allKeys = db.getAllKeys();

	CPPUNIT_ASSERT(allKeys.size() == 4);
	CPPUNIT_ASSERT(allKeys.at(0) == "user_1");
	CPPUNIT_ASSERT(allKeys.at(1) == "user_2");
	CPPUNIT_ASSERT(allKeys.at(2) == "user_3");
	CPPUNIT_ASSERT(allKeys.at(3) == "user_4");

	db.erase(key1);
	db.erase(key2);
	db.erase(key3);
	db.erase(key4);
	db.close();
}
