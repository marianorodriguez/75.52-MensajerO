#ifndef TIME_H_
#define TIME_H_

#include <iostream>
#include <string>

/**
 * Clase encargada de proveer la hora actual del sistema.
 */
class Time {
public:

	/**
	 * @return la hora actual.
	 */
	static std::string getTime();
};


#endif /* TIME_H_ */
