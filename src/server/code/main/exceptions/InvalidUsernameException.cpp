/*
 * InvalidUsernameException.cpp
 *
 *  Created on: 3/4/2015
 *      Author: marian
 */

#include "../../../include/main/exceptions/InvalidUsernameException.h"

InvalidUsernameException::InvalidUsernameException(string what) :
		BaseException(what) {
	Logger::getLogger()->write(Logger::ERROR, what);
}

InvalidUsernameException::~InvalidUsernameException() {}

