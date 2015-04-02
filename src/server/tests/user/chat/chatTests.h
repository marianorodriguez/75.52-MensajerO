/*
 * chatTests.h
 *
 *  Created on: 31/3/2015
 *      Author: marian
 */

#ifndef SERVER_TESTS_USER_CHATTESTS_H_
#define SERVER_TESTS_USER_CHATTESTS_H_

#include "cppunit/extensions/HelperMacros.h"

class chatTests: public CPPUNIT_NS::TestFixture {

	CPPUNIT_TEST_SUITE( chatTests );

	CPPUNIT_TEST(should_serialize_chat);
	CPPUNIT_TEST(should_not_be_a_serialized_chat);
	CPPUNIT_TEST(should_be_a_serialized_chat);
	CPPUNIT_TEST(should_deserialize_chat);
	CPPUNIT_TEST(should_create_new_chat);
	CPPUNIT_TEST(should_add_message);
	CPPUNIT_TEST(should_have_3_sent_messages);

	CPPUNIT_TEST_SUITE_END();

protected:
	void should_serialize_chat();
	void should_be_a_serialized_chat();
	void should_not_be_a_serialized_chat();
	void should_deserialize_chat();
	void should_create_new_chat();
	void should_add_message();
	void should_have_3_sent_messages();
};

#endif /* SERVER_TESTS_USER_CHATTESTS_H_ */
