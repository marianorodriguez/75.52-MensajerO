#ifndef NUMBER_CONVERTER_H
#define NUMBER_CONVERTER_H

#include <string>

class NumberConverter{
public:
	/**
	 * Verifica que sea un número 
	 */
	static bool isNumber(const std::string& str);
	/**
	 * Devuelve el número  representado en el string
	 */
	// TODO mlafroce: tirar excepción si no es número
	static int getNumber(const std::string& str);
	/**
	 * Devuelve el string correspondiente al número
	 */
	static std::string getString(int number);
};

#endif // NUMBER_CONVERTER_H
