/*
 * InvalidUsernameException.h
 *
 *  Created on: 3/4/2015
 *      Author: marian
 */

#ifndef SERVER_MAIN_EXCEPTIONS_INVALIDUSERNAMEEXCEPTION_H_
#define SERVER_MAIN_EXCEPTIONS_INVALIDUSERNAMEEXCEPTION_H_

#include "BaseException.h"

class InvalidUsernameException: public BaseException {
public:
	InvalidUsernameException(string what);
	virtual ~InvalidUsernameException();
};

#endif /* SERVER_MAIN_EXCEPTIONS_INVALIDUSERNAMEEXCEPTION_H_ */
