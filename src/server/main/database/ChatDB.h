/*
 * ChatDB.h
 *
 *  Created on: Apr 3, 2015
 *      Author: fran
 */

#ifndef CHATDB_H_
#define CHATDB_H_

#include "Database.h"

class ChatDB: public Database {
public:
	ChatDB();
	ChatDB(string path);
	void writeChat(string user1, string user2, string value);
	string readChat(string user1, string user2,bool* error);
	void eraseChat(string user1,string user2);
	virtual ~ChatDB();
private:
	string getKey(string user1, string user2);
};

#endif /* CHATDB_H_ */
