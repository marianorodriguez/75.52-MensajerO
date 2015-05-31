/*
 * userTests.cpp
 *
 *  Created on: 3/4/2015
 *      Author: marian
 */

#include "userTests.h"

CPPUNIT_TEST_SUITE_REGISTRATION(userTests);

void userTests::should_have_2_chats() {

	User* user = new User("username", "password");
	user->addChatWithUser("username2");
	user->addChatWithUser("username3");
	CPPUNIT_ASSERT(user->hasChatsWith.size() == 2);
}

void userTests::should_have_no_chats() {

	User* user = new User("username", "password");

	CPPUNIT_ASSERT(user->hasChatsWith.size() == 0);
}

void userTests::should_instantiate_new_user() {

	User* user = new User("username", "password");

	CPPUNIT_ASSERT(user->getUsername() == "username");
	CPPUNIT_ASSERT(user->getPassword() == "password");
	CPPUNIT_ASSERT(user->getLocation() == DEFAULT_USER_LOCATION);
	CPPUNIT_ASSERT(user->getStatus() == DEFAULT_USER_STATUS);
	CPPUNIT_ASSERT(user->getProfilePicture() == DEFAULT_USER_PROFILE_PICTURE);
	CPPUNIT_ASSERT(user->hasChatsWith.size() == 0);
}

void userTests::should_modify_location() {

	User* user = new User("username", "password");

	CPPUNIT_ASSERT(user->getLocation() == DEFAULT_USER_LOCATION);

	user->modifyLocation("AVELLANEDA");

	CPPUNIT_ASSERT(user->getLocation() == "AVELLANEDA");
}

void userTests::should_modify_status() {

	User* user = new User("username", "password");

	CPPUNIT_ASSERT(user->getStatus() == DEFAULT_USER_STATUS);

	user->modifyStatus("busy");

	CPPUNIT_ASSERT(user->getStatus() == "busy");
}

void userTests::should_modify_profile_picture(){

	User* user = new User("username", "password");
	user->modifyProfilePicture("new well-hashed profile picture");

	CPPUNIT_ASSERT(user->getProfilePicture() == "new well-hashed profile picture");
}

void userTests::cant_have_2_chats_with_same_user() {

	User* user = new User("username", "password");
	user->addChatWithUser("some_user");

	CPPUNIT_ASSERT_THROW(user->addChatWithUser("some_user"),
			InvalidUsernameException);
}

void userTests::cant_have_chat_with_himself() {

	User* user = new User("username", "password");

	CPPUNIT_ASSERT_THROW(user->addChatWithUser("username"),
			InvalidUsernameException);
}

void userTests::should_serialize_user() {

	User* user = new User("username", "password");
	user->modifyStatus("newStatus");
	user->addChatWithUser("username2");
	user->addChatWithUser("username3");

	string serializedUser = user->serialize();

	Json::Value jsonUser;

	jsonUser[JSON_USER_LASTTIME] = user->getLastTimeConnected();
	jsonUser[JSON_USER_NAME] = "username";
	jsonUser[JSON_USER_PWD] = "password";
	jsonUser[JSON_USER_LOCATION] = DEFAULT_USER_LOCATION;
	jsonUser[JSON_USER_STATUS] = "newStatus";
	jsonUser[JSON_USER_PROFILE_PICTURE] = DEFAULT_USER_PROFILE_PICTURE;
	jsonUser[JSON_USER_CHATS_WITH][0] = "username2";
	jsonUser[JSON_USER_CHATS_WITH][1] = "username3";

	CPPUNIT_ASSERT(serializedUser == jsonUser.toStyledString());
}

void userTests::should_deserialize_user() {

	User* user1 = new User("username", "password");
	user1->modifyLocation("newLocation");
	user1->addChatWithUser("username2");
	user1->addChatWithUser("username3");

	string serializedUser = user1->serialize();

	User* user2 = new User(serializedUser);

	CPPUNIT_ASSERT(user1->username == user2->username);
	CPPUNIT_ASSERT(user1->password == user2->password);
	CPPUNIT_ASSERT(user1->location == user2->location);
	CPPUNIT_ASSERT(user1->status == user2->status);
	CPPUNIT_ASSERT(user1->hashedProfilePicture == user2->hashedProfilePicture);
	CPPUNIT_ASSERT(user1->hasChatsWith.size() == user2->hasChatsWith.size());
	CPPUNIT_ASSERT(user1->hasChatsWith.at(0) == user2->hasChatsWith.at(0));
	CPPUNIT_ASSERT(user1->hasChatsWith.at(1) == user2->hasChatsWith.at(1));
}

void userTests::should_not_be_a_json_serialized_user(){

	CPPUNIT_ASSERT_THROW(User user("not a serialized User"), NotSerializedDataException);
}
