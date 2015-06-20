#include "services/DeleteChatServiceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(DeleteChatServiceTest);

DeleteChatServiceTest::DeleteChatServiceTest() {}

DeleteChatServiceTest::~DeleteChatServiceTest() {}

void DeleteChatServiceTest::setUp() {
	TestFixture::setUp();

	Database userDB(DATABASE_USERS_PATH);
	User user1("username1", "password1");
	User user2("username2", "password2");
	user1.setLoggedIn(true); user1.setLoginToken(0);
	user2.setLoggedIn(true); user2.setLoginToken(0);
	user1.addChatWithUser("username2");
	user2.addChatWithUser("username1");
	std::vector<std::string> key1, key2;
	key1.push_back("username1");
	key2.push_back("username2");
	userDB.write(key1, user1.serialize());
	userDB.write(key2, user2.serialize());

	Chat chat("username1", "username2");
	chat.addNewMessage(Message("username1", "username2", "firstMessage")); // username1 sends first message to username2
	chat.addNewMessage(Message("username1", "username2", "secondMessage"));	// username1 sends second message to username2
	chat.addNewMessage(Message("username2", "username1", "response"));// username2 replies username1

	Database chatDB(DATABASE_CHATS_PATH);
	std::vector<std::string> chatKey;
	chatKey.push_back("username1");
	chatKey.push_back("username2");
	chatDB.write(chatKey, chat.serialize());
	userDB.close();
	chatDB.close();
}

void DeleteChatServiceTest::tearDown() {
	CppUnit::TestFixture::tearDown();

	Database userDB(DATABASE_USERS_PATH);
	std::vector<std::string> key1, key2;
	key1.push_back("username1");
	key2.push_back("username2");
	userDB.erase(key1);
	userDB.erase(key2);

	Database chatDB(DATABASE_CHATS_PATH);
	std::vector<std::string> chatKey;
	chatKey.push_back("username1");
	chatKey.push_back("username2");
	chatDB.erase(chatKey);

	userDB.close();
	chatDB.close();
}

void DeleteChatServiceTest::testLoggedOutUser(){

	Json::Value input;
	input[SERVICE_USERNAME] = "username1";
	input[SERVICE_PASSWORD] = "password1";
	input[SERVICE_DELETECHAT_WHO] = "username2";
	input[SERVICE_TOKEN] = 0;

	Database userDB(DATABASE_USERS_PATH);
	User user1("username1", "password1");
	user1.setLastTimeConnected();
	user1.setLoggedIn(false); user1.setLoginToken(0);
	vector<string> key; key.push_back("username1");
	userDB.write(key, user1.serialize());
	userDB.close();

	Json::Value output = DeleteChatService::doDeleteChat(input);
	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == false);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == SERVICE_OUT_NOTLOGGEDUSER);

	Database DB(DATABASE_USERS_PATH);
	DB.erase(key);
	DB.close();
}

void DeleteChatServiceTest::testDeleteChat() {

	Json::Value input;
	input[SERVICE_USERNAME] = "username1";
	input[SERVICE_PASSWORD] = "password1";
	input[SERVICE_DELETECHAT_WHO] = "username2";
	input[SERVICE_TOKEN] = 0;

	Json::Value output = DeleteChatService::doDeleteChat(input);

	CPPUNIT_ASSERT(output[SERVICE_OUT_OK].asBool() == true);
	CPPUNIT_ASSERT(output[SERVICE_OUT_WHAT].asString() == "");

	Database chats(DATABASE_CHATS_PATH);
	std::vector<std::string> key;
	key.push_back("username1"); key.push_back("username2");

	Chat chat(chats.read(key));

	CPPUNIT_ASSERT(chat.getFirstMessageUser1() == 3);
	chats.close();
}
