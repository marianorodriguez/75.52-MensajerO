/*
 * BaseException.cpp
 *
 *  Created on: 2/4/2015
 *      Author: marian
 */

#include "../../../include/main/exceptions/BaseException.h"

BaseException::BaseException(const std::string& what) {
	this->description = what;
}

BaseException::~BaseException() {}

std::string BaseException::getDescription() const{
	return this->description;
}

