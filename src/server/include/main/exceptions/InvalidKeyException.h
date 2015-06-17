/*
 * InvalidKeyException.h
 *
 *  Created on: 10/4/2015
 *      Author: marian
 */

#ifndef SERVER_MAIN_EXCEPTIONS_INVALIDKEYEXCEPTION_H_
#define SERVER_MAIN_EXCEPTIONS_INVALIDKEYEXCEPTION_H_

#include <string>
#include "BaseException.h"

class InvalidKeyException: public BaseException {
public:
	InvalidKeyException(const std::string& what);
	virtual ~InvalidKeyException();
};

#endif /* SERVER_MAIN_EXCEPTIONS_INVALIDKEYEXCEPTION_H_ */
