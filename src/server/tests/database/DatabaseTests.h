/*
 * DatabaseTests.h
 *
 *  Created on: Mar 31, 2015
 *      Author: fran
 */

#ifndef DATABASETESTS_H_
#define DATABASETESTS_H_

#include <cppunit/extensions/HelperMacros.h>

class DatabaseTests: public CPPUNIT_NS::TestFixture  {

	CPPUNIT_TEST_SUITE( DatabaseTests );

	CPPUNIT_TEST(should_write_and_read_single_key);
	CPPUNIT_TEST(should_write_and_read_double_keys);
	CPPUNIT_TEST(should_write_and_read_multiple_keys);
	CPPUNIT_TEST(should_erase);
	CPPUNIT_TEST(should_modify);
	CPPUNIT_TEST(should_persist);
	CPPUNIT_TEST(should_not_find_values);
	CPPUNIT_TEST(cant_read_without_keys);
	CPPUNIT_TEST(cant_write_without_keys);
	CPPUNIT_TEST(should_return_all_keys_in_db);

	CPPUNIT_TEST_SUITE_END();

private:

protected:
	void should_write_and_read_single_key();
	void should_write_and_read_double_keys();
	void should_write_and_read_multiple_keys();
	void should_erase();
	void should_modify();
	void should_persist();
	void should_not_find_values();
	void cant_read_without_keys();
	void cant_write_without_keys();
	void should_return_all_keys_in_db();
};

#endif /* DATABASETESTS_H_ */
