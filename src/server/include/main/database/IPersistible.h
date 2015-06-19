/*
 * IPersistible.h
 *
 *  Created on: Mar 31, 2015
 *      Author: fran
 */

#ifndef IPERSISTIBLE_H_
#define IPERSISTIBLE_H_

#include <string>
#include <vector>

using namespace std;

/*
 * Esta clase define una interfaz para objetos que puedan guardar informacion en archivos a partir de una key y un value.
 */

class IPersistible {
public:
	IPersistible();
	virtual ~IPersistible();

	/*
	 * Escribe informacion a partir de @param key y @param value.
	 */
	virtual void write(vector<string> key, const string& value);
	/*
	 * Lee y retorna informacion en @param key.
	 */
	virtual string read(vector<string> key) const ;
};

#endif /* IPERSISTIBLE_H_ */
