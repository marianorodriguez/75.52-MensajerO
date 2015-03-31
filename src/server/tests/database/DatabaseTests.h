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

	CPPUNIT_TEST(should_write_and_read);
	CPPUNIT_TEST(should_erase);
	CPPUNIT_TEST(should_modify);

	CPPUNIT_TEST_SUITE_END();

private:

protected:
	void should_write_and_read();
	void should_erase();
	void should_modify();
};

#endif /* DATABASETESTS_H_ */
