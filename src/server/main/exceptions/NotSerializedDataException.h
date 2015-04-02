/*
 * NotSerializedDataException.h
 *
 *  Created on: 2/4/2015
 *      Author: marian
 */

#ifndef SERVER_MAIN_EXCEPTIONS_NOTSERIALIZEDDATAEXCEPTION_H_
#define SERVER_MAIN_EXCEPTIONS_NOTSERIALIZEDDATAEXCEPTION_H_
#include "BaseException.h"
#include <iostream>
using namespace std;

class NotSerializedDataException: public BaseException {
public:
	NotSerializedDataException(string what);
	virtual ~NotSerializedDataException();
};

#endif /* SERVER_MAIN_EXCEPTIONS_NOTSERIALIZEDDATAEXCEPTION_H_ */
