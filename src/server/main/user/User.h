#ifndef SERVER_MAIN_USER_USER_H_
#define SERVER_MAIN_USER_USER_H_

#include "../interfaces/Serializable/ISerializable.h"
#include <vector>
#include <iostream>
using namespace std;

class User: public ISerializable{
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
};

#endif /* SERVER_MAIN_USER_USER_H_ */
