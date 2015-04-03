#include "chatTests.h"

CPPUNIT_TEST_SUITE_REGISTRATION(chatTests);

void chatTests::should_instantiate_new_chat() {

	string username_1 = "user1";
	string username_2 = "user2";
	Chat chat(username_1, username_2);

	CPPUNIT_ASSERT(chat.username_1 == username_1);
	CPPUNIT_ASSERT(chat.username_2 == username_2);
	CPPUNIT_ASSERT(chat.numberOfMessages == 0);
	CPPUNIT_ASSERT(chat.sentMessages.size() == 0);
}

void chatTests::should_add_message() {

	string username_1 = "user1";
	string username_2 = "user2";
	Chat chat(username_1, username_2);

	string date_time = "29 February, 13:00hs";
	string from = username_1;
	string to = username_2;
	string text = "some random message";
	Message* msg = new Message(date_time, from, to, text);

	chat.addNewMessage(msg);

	Message* addedMsg = chat.sentMessages.at(0);

	CPPUNIT_ASSERT(addedMsg == msg);
	CPPUNIT_ASSERT(addedMsg->getText() == text);

	delete msg;
}

void chatTests::should_have_3_sent_messages() {

	string date_time = "29 February, 13:00hs";
	string from = "user1";
	string to = "user2";
	Chat chat(from, to);
	chat.addNewMessage(new Message(date_time, from, to, "first message"));
	chat.addNewMessage(new Message(date_time, to, from, "second message"));
	chat.addNewMessage(new Message(date_time, from, to, "third message"));

	CPPUNIT_ASSERT(chat.numberOfMessages == 3);
}

void chatTests::should_serialize_chat() {

	string date_time = "29 February, 13:00hs";
	string from = "user1";
	string to = "user2";
	Chat chat(from, to);
	Message* m1 = new Message(date_time, from, to, "first message");
	Message* m2 = new Message(date_time, to, from, "second message");
	Message* m3 = new Message(date_time, from, to, "third message");

	chat.addNewMessage(m1);
	chat.addNewMessage(m2);
	chat.addNewMessage(m3);

	Json::Value JsonChat;
	JsonChat[JSON_CHAT_ROOT][JSON_CHAT_USER_1] = from;
	JsonChat[JSON_CHAT_ROOT][JSON_CHAT_USER_2] = to;
	JsonChat[JSON_CHAT_ROOT][JSON_CHAT_NUM_MSG] = 3;
	JsonChat[JSON_CHAT_ROOT][JSON_CHAT_MESSAGES][0] = m1->serialize();
	JsonChat[JSON_CHAT_ROOT][JSON_CHAT_MESSAGES][1] = m2->serialize();
	JsonChat[JSON_CHAT_ROOT][JSON_CHAT_MESSAGES][2] = m3->serialize();

	CPPUNIT_ASSERT(JsonChat.toStyledString() == chat.serialize());

	delete m1;
	delete m2;
	delete m3;
}

void chatTests::should_not_be_a_serialized_chat() {

	string serialized = "not a serialized Chat";
	CPPUNIT_ASSERT_THROW(Chat c(serialized), NotSerializedDataException);
}

void chatTests::should_deserialize_chat() {

	string date_time = "29 February, 13:00hs";
	string from = "user1";
	string to = "user2";
	Chat chat1(from, to);
	Message* m1 = new Message(date_time, from, to, "some message");
	Message* m2 = new Message(date_time, to, from, "another message");

	chat1.addNewMessage(m1);
	chat1.addNewMessage(m2);

	string serializedChat = chat1.serialize();

	Chat chat2(serializedChat);

	CPPUNIT_ASSERT(chat1.username_1 == chat2.username_1);
	CPPUNIT_ASSERT(chat1.username_2 == chat2.username_2);
	CPPUNIT_ASSERT(chat1.numberOfMessages == chat2.numberOfMessages);
	CPPUNIT_ASSERT(
			chat1.sentMessages.at(0)->getText()
					== chat2.sentMessages.at(0)->getText());
	CPPUNIT_ASSERT(
			chat1.sentMessages.at(1)->getText()
					== chat2.sentMessages.at(1)->getText());

	delete m1;
	delete m2;
}

void chatTests::cant_add_message_between_invalid_users() {

	Chat chat("username1", "username2");

	chat.addNewMessage(new Message("", "username1", "username2", "text"));
	chat.addNewMessage(new Message("", "username2", "username1", "text"));

	CPPUNIT_ASSERT_THROW(
			chat.addNewMessage(
					new Message("", "invalidUser", "username2", "text")),
			InvalidUsernameException);
}

void chatTests::cant_create_chat_between_one_single_user() {

	CPPUNIT_ASSERT_THROW(Chat c("user1", "user1"), InvalidUsernameException);
}
