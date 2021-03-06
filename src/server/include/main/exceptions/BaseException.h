/*
 * BaseException.h
 *
 *  Created on: 2/4/2015
 *      Author: marian
 */

#ifndef SERVER_MAIN_EXCEPTIONS_BASEEXCEPTION_H_
#define SERVER_MAIN_EXCEPTIONS_BASEEXCEPTION_H_

#include <exception>
#include <string>
/**
 * Define una clase base para todas las excepciones del servidor.
 */
class BaseException: public std::exception {
public:
	explicit BaseException(const std::string& what);
	virtual ~BaseException();

	std::string getDescription() const;
private:
	std::string description;
};

#endif /* SERVER_MAIN_EXCEPTIONS_BASEEXCEPTION_H_ */
