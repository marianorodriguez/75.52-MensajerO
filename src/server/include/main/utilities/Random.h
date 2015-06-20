/*
 * Random.h
 *
 *  Created on: 20/6/2015
 *      Author: marian
 */

#ifndef CODE_MAIN_UTILITIES_RANDOM_H_
#define CODE_MAIN_UTILITIES_RANDOM_H_

#include <random>

class Random {
public:
	Random();
	virtual ~Random();

	static double getRandom();
};

#endif /* CODE_MAIN_UTILITIES_RANDOM_H_ */
