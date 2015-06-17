/*
 * KeyNotFoundException.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: fran
 */

#include "../../../include/main/exceptions/KeyNotFoundException.h"

KeyNotFoundException::KeyNotFoundException(const std::string& what): BaseException(what) {

}


KeyNotFoundException::~KeyNotFoundException() {
}

