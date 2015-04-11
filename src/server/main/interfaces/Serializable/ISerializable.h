/*
 * ISerializable.h
 *
 *  Created on: 29/3/2015
 *      Author: marian
 */

#ifndef SERVER_MAIN_INTERFACES_ISERIALIZABLE_H_
#define SERVER_MAIN_INTERFACES_ISERIALIZABLE_H_

#include "json/json.h"
#include <iostream>
using namespace std;

/**
 * Esta clase define una interfaz para todos los objetos que se pueden serializar a una cadena de texto.
 */
class ISerializable{

public:
	ISerializable();
	virtual ~ISerializable();

	/**
	 * @returns El objeto serializado como una cadena de texto.
	 */
	virtual string serialize() const;
};

#endif /* SERVER_MAIN_INTERFACES_ISERIALIZABLE_H_ */
