/*
 * InvalidUsernameException.cpp
 *
 *  Created on: 3/4/2015
 *      Author: marian
 */

#include "../../../include/main/exceptions/InvalidUsernameException.h"
#include "../../../include/main/utilities/Logger.h"

InvalidUsernameException::InvalidUsernameException(const std::string& what) :
		BaseException(what) {
	Logger::getLogger()->write(Logger::ERROR, what);
}

InvalidUsernameException::~InvalidUsernameException() {}

