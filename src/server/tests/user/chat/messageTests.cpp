#include <cppunit/config/SourcePrefix.h>
#include "messageTests.h"
#include "../../../main/user/chat/Message.h"
#include "../../main/config.h"
#include <stdio.h>
#include <iostream>
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(messageTests);

void messageTests::should_instantiate_message() {

	string date = "2 march";
	string from = "user1";
	string to = "user2";
	string message = "some random message";

	Message m(date, from, to, message);

	CPPUNIT_ASSERT(m.userFromID == from);
	CPPUNIT_ASSERT(m.userToID == to);
	CPPUNIT_ASSERT(m.message == message);
	CPPUNIT_ASSERT(m.date_time == date);

}

void messageTests::should_serialize_message() {

	ISerializable serializer;

	string date = "Feb 3, 15:30hs";
	string from = "user1";
	string to = "user2";
	string message = "some random message to serialize";

	Message m(date, from, to, message);

	string serialized = m.serialize();

	Json::Value jsonMsg;
	jsonMsg[JSON_MSG_ROOT][JSON_MSG_FROM_VALUE] = m.userFromID;
	jsonMsg[JSON_MSG_ROOT][JSON_MSG_TO_VALUE] = m.userToID;
	jsonMsg[JSON_MSG_ROOT][JSON_MSG_DATE_TIME_VALUE] = m.date_time;
	jsonMsg[JSON_MSG_ROOT][JSON_MSG_TEXT] = m.message;

	CPPUNIT_ASSERT(serialized == jsonMsg.toStyledString());
}

void messageTests::should_deserialize_message() {

	ISerializable serializer;
	string date = "14 Aug";
	string from = "user2";
	string to = "user1";
	string message = "some random message to serialize";

	Message m1(date, from, to, message);

	string serializedString = m1.serialize();

	Message m2(serializedString);

	CPPUNIT_ASSERT(m1.userToID == m2.userToID);
	CPPUNIT_ASSERT(m1.userFromID == m2.userFromID);
	CPPUNIT_ASSERT(m1.date_time == m2.date_time);
	CPPUNIT_ASSERT(m1.message == m2.message);
}

void messageTests::should_not_be_a_serialized_message() {

	string serialized = "this is not a JSON serialized message";
	CPPUNIT_ASSERT_THROW(Message msg(serialized), NotSerializedDataException);
}

void messageTests::cant_add_message_between_the_same_user() {

	CPPUNIT_ASSERT_THROW(Message m("", "user1", "user1", "text"),
			InvalidUsernameException);
}
