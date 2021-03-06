/*
 * InvalidKeyException.cpp
 *
 *  Created on: 10/4/2015
 *      Author: marian
 */

#include "../../../include/main/exceptions/InvalidKeyException.h"

InvalidKeyException::InvalidKeyException(const std::string& what): BaseException(what) {
	Logger::getLogger()->write(Logger::ERROR, what);
}

InvalidKeyException::~InvalidKeyException() {
}

