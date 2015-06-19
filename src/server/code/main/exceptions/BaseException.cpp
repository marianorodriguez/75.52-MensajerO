/*
 * BaseException.cpp
 *
 *  Created on: 2/4/2015
 *      Author: marian
 */

#include "../../../include/main/exceptions/BaseException.h"

BaseException::BaseException(string what) {
	this->description = what;
	Logger::getLogger()->write(Logger::ERROR, what);
}

BaseException::~BaseException() {}

string BaseException::getDescription() const{
	return this->description;
}

