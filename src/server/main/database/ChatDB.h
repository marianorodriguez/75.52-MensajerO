/*
 * ChatDB.h
 *
 *  Created on: Apr 3, 2015
 *      Author: fran
 */

#ifndef CHATDB_H_
#define CHATDB_H_

#include "Database.h"

/*
 * This class defines a database where the chats between users are located.
 * Key = user1 + user2
 * Value = messages between the 2 users
 * The methods are the same as it's father Database but it receives two users
 * instead of a key as the key is formed from the two users. The order in which
 * the users are received as parameters doesn't matter, two users will always form the same key.
 */
class ChatDB: public Database {
public:
	ChatDB();
	ChatDB(string path);
	void writeChat(string user1, string user2, string value);
	string readChat(string user1, string user2,bool* error);
	void eraseChat(string user1,string user2);
	virtual ~ChatDB();
private:
	/*
	 * Receives two users and forms a key.
	 */
	string getKey(string user1, string user2);
};

#endif /* CHATDB_H_ */
