/*
 * FileNotFoundException.cpp
 *
 *  Created on: 4/4/2015
 *      Author: marian
 */

#include "FileNotFoundException.h"

FileNotFoundException::FileNotFoundException(string what) :
		BaseException(what) {}

FileNotFoundException::~FileNotFoundException() {}

