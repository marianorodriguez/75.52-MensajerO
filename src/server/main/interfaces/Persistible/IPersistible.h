/*
 * IPersistible.h
 *
 *  Created on: Mar 31, 2015
 *      Author: fran
 */

#ifndef IPERSISTIBLE_H_
#define IPERSISTIBLE_H_

#include <string>
using namespace std;

class IPersistible {
public:
	IPersistible();
	virtual ~IPersistible();

	virtual void write(string key, string value);
	virtual string read(string key,bool* error);
};

#endif /* IPERSISTIBLE_H_ */
