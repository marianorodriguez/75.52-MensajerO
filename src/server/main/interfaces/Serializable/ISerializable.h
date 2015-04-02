/*
 * ISerializable.h
 *
 *  Created on: 29/3/2015
 *      Author: marian
 */

#ifndef SERVER_MAIN_INTERFACES_ISERIALIZABLE_H_
#define SERVER_MAIN_INTERFACES_ISERIALIZABLE_H_

#include <iostream>
using namespace std;

class ISerializable{

public:
	ISerializable();
	virtual ~ISerializable();

	virtual string serialize();
	virtual void deserialize(string serializedData);

};

#endif /* SERVER_MAIN_INTERFACES_ISERIALIZABLE_H_ */