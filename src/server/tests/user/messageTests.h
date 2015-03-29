/*
 * messageTests.h
 *
 *  Created on: 29/3/2015
 *      Author: marian
 */

#ifndef SERVER_TESTS_USER_MESSAGETESTS_H_
#define SERVER_TESTS_USER_MESSAGETESTS_H_

#include <cppunit/extensions/HelperMacros.h>

class messageTests: public CPPUNIT_NS::TestFixture {

	CPPUNIT_TEST_SUITE( messageTests );

	CPPUNIT_TEST(should_instantiate_message);
	CPPUNIT_TEST(should_serialize_message);
	CPPUNIT_TEST(should_deserialize_message);

	CPPUNIT_TEST_SUITE_END();

private:

protected:
	void should_instantiate_message();
	void should_serialize_message();
	void should_deserialize_message();
};

#endif /* SERVER_TESTS_USER_MESSAGETESTS_H_ */
