#ifndef NUMBER_CONVERTER_H
#define NUMBER_CONVERTER_H

#include <string>

class NumberConverter{
public:
	/**
	 * Verifica que @param str sea un número
	 */
	static bool isNumber(const std::string& str);

	// TODO mlafroce: tirar excepción si no es número
	/**
	 * Devuelve el número  representado en el string
	 */
	static int getNumber(const std::string& str);

	/**
	 * Devuelve el string correspondiente al @param number
	 */
	static std::string getString(int number);
};

#endif // NUMBER_CONVERTER_H
