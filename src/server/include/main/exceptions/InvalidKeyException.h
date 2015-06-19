/*
 * InvalidKeyException.h
 *
 *  Created on: 10/4/2015
 *      Author: marian
 */

#ifndef SERVER_MAIN_EXCEPTIONS_INVALIDKEYEXCEPTION_H_
#define SERVER_MAIN_EXCEPTIONS_INVALIDKEYEXCEPTION_H_

#include "BaseException.h"
#include "../../../include/main/utilities/Logger.h"

/**
 * Define una excepcion de tipo "key invalida"
 * Se lanza cuando, en la base de datos, se usa una key que no se puede procesar.
 */
class InvalidKeyException: public BaseException {
public:
	InvalidKeyException(string what);
	virtual ~InvalidKeyException();
};

#endif /* SERVER_MAIN_EXCEPTIONS_INVALIDKEYEXCEPTION_H_ */
