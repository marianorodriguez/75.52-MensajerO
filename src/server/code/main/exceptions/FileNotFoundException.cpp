/*
 * FileNotFoundException.cpp
 *
 *  Created on: 4/4/2015
 *      Author: marian
 */

#include "../../../include/main/exceptions/FileNotFoundException.h"

FileNotFoundException::FileNotFoundException(const std::string& what) :
		BaseException(what) {}

FileNotFoundException::~FileNotFoundException() {}

