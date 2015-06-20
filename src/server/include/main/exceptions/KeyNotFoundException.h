/*
 * KeyNotFoundException.h
 *
 *  Created on: Apr 5, 2015
 *      Author: fran
 */

#ifndef KEYNOTFOUNDEXCEPTION_H_
#define KEYNOTFOUNDEXCEPTION_H_

#include "BaseException.h"
#include "../../../include/main/utilities/Logger.h"
#include <iostream>
using namespace std;

/*
 * Define una excepcion de tipo "key no encontrada"
 * Esta excepcion se lanza cuando no se encuentra una key en la base de datos.
 */
class KeyNotFoundException: public BaseException  {
public:
	KeyNotFoundException(string what);
	virtual ~KeyNotFoundException();
};

#endif /* KEYNOTFOUNDEXCEPTION_H_ */
