#include <cppunit/config/SourcePrefix.h>
#include "../../../include/tests/user/chat/MessageTests.h"
#include "../../include/main/user/chat/Message.h"
#include <stdio.h>
#include <iostream>
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(messageTests);

void messageTests::should_instantiate_message() {

	string from = "user1";
	string to = "user2";
	string message = "some random message";

	Message m(from, to, message);

	CPPUNIT_ASSERT(m.userFromID == from);
	CPPUNIT_ASSERT(m.userToID == to);
	CPPUNIT_ASSERT(m.message == message);
	CPPUNIT_ASSERT(m.sent == false);
}

void messageTests::should_serialize_message() {
	string from = "user1";
	string to = "user2";
	string message = "some random message to serialize";

	Message m(from, to, message);

	string serialized = m.serialize();

	Json::Value jsonMsg;
	jsonMsg[JSON_MSG_FROM_VALUE] = m.userFromID;
	jsonMsg[JSON_MSG_TO_VALUE] = m.userToID;
	jsonMsg[JSON_MSG_DATE_VALUE] = m.date;
	jsonMsg[JSON_MSG_TIME_VALUE] = m.time;
	jsonMsg[JSON_MSG_TEXT] = m.message;
	jsonMsg[JSON_MSG_SENT] = m.sent;

	CPPUNIT_ASSERT(serialized == jsonMsg.toStyledString());
}

void messageTests::should_deserialize_message() {

	string from = "user2";
	string to = "user1";
	string message = "some random message to serialize";

	Message m1(from, to, message);

	string serializedString = m1.serialize();

	Message m2(serializedString);

	CPPUNIT_ASSERT(m1.userToID == m2.userToID);
	CPPUNIT_ASSERT(m1.userFromID == m2.userFromID);
	CPPUNIT_ASSERT(m1.date == m2.date);
	CPPUNIT_ASSERT(m1.time == m2.time);
	CPPUNIT_ASSERT(m1.message == m2.message);
	CPPUNIT_ASSERT(m1.sent == m2.sent);
}

void messageTests::should_not_be_a_serialized_message() {

	string serialized = "this is not a JSON serialized message";
	CPPUNIT_ASSERT_THROW(Message msg(serialized), NotSerializedDataException);
}

void messageTests::cant_add_message_between_the_same_user() {

	CPPUNIT_ASSERT_THROW(Message m("user1", "user1", "text"),
			InvalidUsernameException);
}
