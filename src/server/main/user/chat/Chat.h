/*
 * Chat.h
 *
 *  Created on: 2/4/2015
 *      Author: marian
 */

#ifndef SERVER_MAIN_USER_CHAT_CHAT_H_
#define SERVER_MAIN_USER_CHAT_CHAT_H_

#include "../../interfaces/Serializable/ISerializable.h"
#include "../../exceptions/InvalidUsernameException.h"
#include "../../../tests/user/chat/chatTests.h"
#include "Message.h"

class chatTests;
class Chat: public ISerializable {
	friend chatTests;

public:
	Chat(string serializedChat);
	Chat(string user1, string user2);
	virtual ~Chat();
	void addNewMessage(Message* msg);

	string serialize() override;

private:
	string username_1;
	string username_2;
	int numberOfMessages;
	vector<Message*> sentMessages;
};

#endif /* SERVER_MAIN_USER_CHAT_CHAT_H_ */
