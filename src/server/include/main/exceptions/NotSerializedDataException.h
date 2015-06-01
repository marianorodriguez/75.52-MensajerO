/*
 * NotSerializedDataException.h
 *
 *  Created on: 2/4/2015
 *      Author: marian
 */

#ifndef SERVER_MAIN_EXCEPTIONS_NOTSERIALIZEDDATAEXCEPTION_H_
#define SERVER_MAIN_EXCEPTIONS_NOTSERIALIZEDDATAEXCEPTION_H_
#include "BaseException.h"
#include <iostream>
using namespace std;

/**
 * Define una excepcion de tipo "no es un objeto serializado".
 * El objeto no es serializado cuando:
 * -> No se reconoce a la cadena de texto como un mensaje serializado.
 * -> No se reconoce a la cadena de texto como un chat serializado.
 * -> No se reconoce a la cadena de texto como un usuario serializado.
 */
class NotSerializedDataException: public BaseException {
public:
	NotSerializedDataException(string what);
	virtual ~NotSerializedDataException();
};

#endif /* SERVER_MAIN_EXCEPTIONS_NOTSERIALIZEDDATAEXCEPTION_H_ */
