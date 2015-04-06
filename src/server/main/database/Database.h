/*
 * Database.h
 *
 *  Created on: Mar 31, 2015
 *      Author: fran
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <iostream>
#include <algorithm>
#include <rocksdb/db.h>
#include "json/json.h"
#include "../interfaces/Persistible/IPersistible.h"
#include "../exceptions/KeyNotFoundException.h"
#include "../logger/Logger.h"

/*
 * Esta clase define una base de datos donde la informacion se guarda como key-value.
 */

class Database: public IPersistible {
private:
	rocksdb::DB* database;
public:
	Database();
	/*
	 * Abre la base de datos en el @param path especificado. Si la base de datos no existe, la crea.
	 */
	Database(string path);

	/*
	 * Escribe informacion en la bd. Si @param key ya existe, el nuevo @param value reemplaza al anterior.
	 * No importa el orden de los strings dentro del vector, los mismos strings siempre forman la misma key.
	 */
	void write(vector<string> key, string value) override;

	/*
	 * Retorna el value indicado por @param key. Si la key no existe, retorna @param error = true, si existe falso.
	 */
	string read(vector<string> key) override;

	/*
	 * Borra el @param key con el value asociado de la bd.
	 */
	void erase(vector<string> key);
	virtual ~Database();

private:
	/*
	 * Forma una key a partir de un vector de strings.
	 */
	string getKey(vector<string> key);
};

#endif /* DATABASE_H_ */
