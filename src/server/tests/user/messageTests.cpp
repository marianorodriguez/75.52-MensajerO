#include <cppunit/config/SourcePrefix.h>
#include "messageTests.h"
#include "../../main/user/Message.h"
#include <stdio.h>
#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(messageTests);

void messageTests::should_instantiate_message() {

	string date = "2 march";
	int num = 1;
	int from = 23;
	int to = 34;
	string message = "some random message";
	Message m(num, date, from, to, message);

	CPPUNIT_ASSERT(m.msg_number == num);
	CPPUNIT_ASSERT(m.userFromID == from);
	CPPUNIT_ASSERT(m.userToID == to);
	CPPUNIT_ASSERT(m.message == message);
	CPPUNIT_ASSERT(m.date_time == date);

}

void messageTests::should_serialize_message() {

	ISerializable serializer;

	int num = 2;
	string date = "Feb 3, 15:30hs";
	int from = 23;
	int to = 34;
	string message = "some random message to serialize";

	Message m(num, date, from, to, message);

	string serialized = m.serialize();

	Json::Value jsonMsg;
	jsonMsg["message"]["msg_number"] = m.msg_number;
	jsonMsg["message"]["fromID"] = m.userFromID;
	jsonMsg["message"]["toID"] = m.userToID;
	jsonMsg["message"]["date_time"] = m.date_time;
	jsonMsg["message"]["text"] = m.message;


	CPPUNIT_ASSERT(serialized == jsonMsg.toStyledString());
}

void messageTests::should_deserialize_message() {

	ISerializable serializer;
	string date = "14 Aug";
	int num = 2;
	int from = 23;
	int to = 34;
	string message = "some random message to serialize";

	Message m1(num, date, from, to, message);

	string serialized = m1.serialize();

	Message m2;
	m2.deserialize(serialized);

	CPPUNIT_ASSERT(m1.userToID == m2.userToID);
	CPPUNIT_ASSERT(m1.userFromID == m2.userFromID);
	CPPUNIT_ASSERT(m1.message == m2.message);
	CPPUNIT_ASSERT(m1.date_time == m2.date_time);
	CPPUNIT_ASSERT(m1.message == m2.message);
}
