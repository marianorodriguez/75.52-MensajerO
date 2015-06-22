/*
 * FileNotFoundException.cpp
 *
 *  Created on: 4/4/2015
 *      Author: marian
 */

#include "../../../include/main/exceptions/FileNotFoundException.h"
#include <../../include/main/utilities/Logger.h>

FileNotFoundException::FileNotFoundException(const std::string& what) :
		BaseException(what) {
	Logger::getLogger()->write(Logger::ERROR, what);
}

FileNotFoundException::~FileNotFoundException() {}

