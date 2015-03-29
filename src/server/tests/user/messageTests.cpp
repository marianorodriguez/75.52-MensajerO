#include <cppunit/config/SourcePrefix.h>
#include "messageTests.h"
#include "../../main/user/Message.h"
#include "../../main/config.h"
#include <stdio.h>
#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(messageTests);

void messageTests::should_instantiate_message() {

	int from = 23;
	int to = 34;
	string message = "some random message";
	Message m(from, to, message);

	CPPUNIT_ASSERT(m.userFromID == from);
	CPPUNIT_ASSERT(m.userToID == to);
	CPPUNIT_ASSERT(m.message == message);

}

void messageTests::should_serialize_message() {

	int from = 23;
	int to = 34;
	string message = "some random message to serialize";

	Message m(from, to, message);
	string serialized = m.serialize();

	string shouldSay =
			StringUtil::int2string(from) + MESSAGE_FIELD_SEPARATOR +
			StringUtil::int2string(to) + MESSAGE_FIELD_SEPARATOR +
			message;

	CPPUNIT_ASSERT(serialized == shouldSay);
}

void messageTests::should_deserialize_message() {

	int from = 23;
	int to = 34;
	string message = "some random message to serialize";

	Message m1(from, to, message);
	string serialized = m1.serialize();

	Message m2;
	m2.deserialize(serialized);

	CPPUNIT_ASSERT(m1.userToID == m2.userToID);
	CPPUNIT_ASSERT(m1.userFromID == m2.userFromID);
	CPPUNIT_ASSERT(m1.message == m2.message);
}
