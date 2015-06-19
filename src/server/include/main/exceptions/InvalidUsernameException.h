/*
 * InvalidUsernameException.h
 *
 *  Created on: 3/4/2015
 *      Author: marian
 */

#ifndef SERVER_MAIN_EXCEPTIONS_INVALIDUSERNAMEEXCEPTION_H_
#define SERVER_MAIN_EXCEPTIONS_INVALIDUSERNAMEEXCEPTION_H_

#include "BaseException.h"
#include "../../../include/main/utilities/Logger.h"

/**
 * Define una excepcion de tipo "usuario invalido".
 * Un usuario puede ser invalido por las siguientes razones:
 * ->Al querer un usuario comenzar un chat con otro con el que ya tiene un chat iniciado.
 * ->Al querer un usuario comenzar un chat con el mismo.
 * ->Al querer un usuario mandarse un mensaje a el mismo.
 * ->Al querer enviar un mensaje entre los mismos usuarios.
 */
class InvalidUsernameException: public BaseException {
public:
	InvalidUsernameException(string what);
	virtual ~InvalidUsernameException();
};

#endif /* SERVER_MAIN_EXCEPTIONS_INVALIDUSERNAMEEXCEPTION_H_ */
