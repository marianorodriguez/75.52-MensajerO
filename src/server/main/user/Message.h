#ifndef SERVER_MAIN_USER_MESSAGE_H_
#define SERVER_MAIN_USER_MESSAGE_H_
#include "../interfaces/Serializable/ISerializable.h"
#include "json/json.h"
#include "../../tests/user/messageTests.h"
#include<iostream>
using namespace std;

/**
 * Esta clase define un único mensaje entre dos usuarios.
 */
class Message: public ISerializable {

	friend messageTests;

public:
	Message(string toDeserialize);
	Message(string date_time, string from, string to, string message);
	virtual ~Message();

	string serialize() override;

private:
	string userFromID;
	string userToID;
	string date_time;
	string message;
};

#endif /* SERVER_MAIN_USER_MESSAGE_H_ */
