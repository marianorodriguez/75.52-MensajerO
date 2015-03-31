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
	Message();
	Message(int msg_num,string date_time, int from, int to, string message);
	virtual ~Message();

	string serialize() override;
	void deserialize(string serialized) override;

private:
	int msg_number;
	int userFromID;
	int userToID;
	string date_time;
	string message;
};

#endif /* SERVER_MAIN_USER_MESSAGE_H_ */
