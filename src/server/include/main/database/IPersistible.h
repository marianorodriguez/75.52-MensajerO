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

/**
 * Esta clase define una interfaz para objetos que puedan guardar
 * informacion en archivos a partir de una key y un value.
 */

class IPersistible {
public:
	IPersistible();
	virtual ~IPersistible();

	/*
	 * Escribe informacion a partir de @param key y @param value.
	 */
	virtual void write(const std::vector<std::string>& key, const std::string& value) = 0;
	/*
	 * Lee y retorna informacion en @param key.
	 */
	virtual std::string read(const std::vector<std::string>& key) const = 0 ;
};

#endif /* IPERSISTIBLE_H_ */
