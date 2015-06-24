#include "services/DeleteChatServiceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(DeleteChatServiceTest);

DeleteChatServiceTest::~DeleteChatServiceTest() {
}

void DeleteChatServiceTest::setUp() {
	ServiceTest::setUp();

	this->service = new DeleteChatService(*userDB, *chatDB);

	User user1("username1", "password1");
	User user2("username2", "password2");
	user1.addChatWithUser("username2");
	user2.addChatWithUser("username1");
	std::vector<std::string> key1, key2;
	key1.push_back("username1");
	key2.push_back("username2");
	userDB->write(key1, user1.serialize());
	userDB->write(key2, user2.serialize());

	Chat chat("username1", "username2");
	chat.addNewMessage(Message("username1", "username2", "firstMessage")); // username1 sends first message to username2
	chat.addNewMessage(Message("username1", "username2", "secondMessage"));	// username1 sends second message to username2
	chat.addNewMessage(Message("username2", "username1", "response"));// username2 replies username1

	std::vector<std::string> chatKey;
	chatKey.push_back("username1");
	chatKey.push_back("username2");
	chatDB->write(chatKey, chat.serialize());
}

void DeleteChatServiceTest::tearDown() {

	std::vector<std::string> key1, key2;
	key1.push_back("username1");
	key2.push_back("username2");
	userDB->erase(key1);
	userDB->erase(key2);

	std::vector<std::string> chatKey;
	chatKey.push_back("username1");
	chatKey.push_back("username2");
	chatDB->erase(chatKey);

	ServiceTest::tearDown();
}

void DeleteChatServiceTest::testDeleteChat() {

	Json::Value input;
	input[SERVICE_USERNAME] = "username1";
	input[SERVICE_PASSWORD] = "password1";
	input[SERVICE_DELETECHAT_WHO] = "username2";

	string output = service->executeRequest(input.toStyledString());
	Json::Value jsonOut;
	Json::Reader reader;
	reader.parse(output, jsonOut);

	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(jsonOut[SERVICE_OUT_WHAT].asString() == "");

	std::vector<std::string> key;
	key.push_back("username1");
	key.push_back("username2");

	Chat chat(chatDB->read(key));

	CPPUNIT_ASSERT(chat.getFirstMessageUser1() == 3);
}
