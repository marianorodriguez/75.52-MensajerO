/*
 * userTests.h
 *
 *  Created on: 3/4/2015
 *      Author: marian
 */

#ifndef SERVER_TESTS_USER_USERTESTS_H_
#define SERVER_TESTS_USER_USERTESTS_H_

#include "cppunit/extensions/HelperMacros.h"
#include "../../main/user/User.h"
#include "../../main/config.h"

class userTests: public CPPUNIT_NS::TestFixture {

	CPPUNIT_TEST_SUITE( userTests );

	CPPUNIT_TEST(should_instantiate_new_user);
	CPPUNIT_TEST(should_modify_location);
	CPPUNIT_TEST(should_modify_status);
	CPPUNIT_TEST(should_modify_profile_picture);
	CPPUNIT_TEST(should_have_no_chats);
	CPPUNIT_TEST(should_have_2_chats);
	CPPUNIT_TEST(should_serialize_user);
	CPPUNIT_TEST(should_deserialize_user);
	CPPUNIT_TEST(cant_have_chat_with_himself);
	CPPUNIT_TEST(cant_have_2_chats_with_same_user);
	CPPUNIT_TEST(should_not_be_a_json_serialized_user);

	CPPUNIT_TEST_SUITE_END();

protected:
	void should_instantiate_new_user();
	void should_encrypt_password();
	void should_modify_location();
	void should_modify_status();
	void should_modify_profile_picture();
	void should_have_no_chats();
	void should_have_2_chats();
	void should_serialize_user();
	void should_deserialize_user();
	void cant_have_chat_with_himself();
	void cant_have_2_chats_with_same_user();
	void should_not_be_a_json_serialized_user();
};

#endif /* SERVER_TESTS_USER_USERTESTS_H_ */
