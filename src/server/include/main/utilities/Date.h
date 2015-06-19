#ifndef DATE_H_
#define DATE_H_

#include <string>

/**
 * Clase encargada de proveer la fecha actual.
 */
class Date {
public:
	/**
	 * Devuelve la fecha actual.
	 */
	static std::string getDate();
};

#endif /* DATE_H_ */
