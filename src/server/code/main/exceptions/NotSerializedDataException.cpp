/*
 * NotSerializedDataException.cpp
 *
 *  Created on: 2/4/2015
 *      Author: marian
 */

#include "../../../include/main/exceptions/NotSerializedDataException.h"

NotSerializedDataException::NotSerializedDataException(string what):
		BaseException(what) {
	Logger::getLogger()->write(Logger::ERROR, what);
}

NotSerializedDataException::~NotSerializedDataException() {}

