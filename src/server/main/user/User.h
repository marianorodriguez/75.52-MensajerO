#ifndef SERVER_MAIN_USER_USER_H_
#define SERVER_MAIN_USER_USER_H_

#include "../interfaces/Serializable/ISerializable.h"
#include "../exceptions/InvalidUsernameException.h"
#include "../exceptions/NotSerializedDataException.h"
#include "../../tests/user/userTests.h"
#include "../utilities/MD5.h"
#include <vector>
#include <iostream>
using namespace std;

class userTests;
class User: public ISerializable{
	friend userTests;

public:
	User(string username, string pass);
	User(string serializedUser);
	virtual ~User();

	string serialize() override;

	string getUsername();
	string getHashedPWD();
	string getLocation();
	string getStatus();

	void modifyLocation(string newLocation);
	void modifyStatus(string newStatus);
	void addChatWithUser(string user);

private:
	string username;
	string hashedPWD;
	string location;
	string status;
	int numberOfChats;
	vector<string> hasChatsWith;

	string encryptPassword(string plainPWD);
	bool isChattingWith(string username);
};

#endif /* SERVER_MAIN_USER_USER_H_ */
