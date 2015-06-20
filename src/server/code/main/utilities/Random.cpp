/*
 * Random.cpp
 *
 *  Created on: 20/6/2015
 *      Author: marian
 */

#include "../../../include/main/utilities/Random.h"

Random::Random() {}

Random::~Random() {}

double Random::getRandom(){
	srand(time(0));
	return rand();
}
