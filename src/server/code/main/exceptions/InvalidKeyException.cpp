/*
 * InvalidKeyException.cpp
 *
 *  Created on: 10/4/2015
 *      Author: marian
 */

#include "../../../include/main/exceptions/InvalidKeyException.h"

InvalidKeyException::InvalidKeyException(string what): BaseException(what) {}

InvalidKeyException::~InvalidKeyException() {
}

