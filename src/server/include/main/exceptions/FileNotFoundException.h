/*
 * FileNotFoundException.h
 *
 *  Created on: 4/4/2015
 *      Author: marian
 */

#ifndef SERVER_MAIN_EXCEPTIONS_FILENOTFOUNDEXCEPTION_H_
#define SERVER_MAIN_EXCEPTIONS_FILENOTFOUNDEXCEPTION_H_

#include <string>
#include "BaseException.h"
#include "../../../include/main/utilities/Logger.h"

/**
 * Define una excepción de tipo "archivo no encontrado".
 * Esta excepción se lanza cuando no se encuentra algún archivo dada la ruta usada.
 */
class FileNotFoundException: public BaseException {
public:
	FileNotFoundException(const std::string& what);
	virtual ~FileNotFoundException();
};

#endif /* SERVER_MAIN_EXCEPTIONS_FILENOTFOUNDEXCEPTION_H_ */
