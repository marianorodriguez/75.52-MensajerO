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
#include <string>
#include <rocksdb/db.h>
#include "json/json.h"
#include "IPersistible.h"
#include "exceptions/KeyNotFoundException.h"
#include "exceptions/InvalidKeyException.h"
#include "utilities/Logger.h"

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
	Database(const string& path);

	/*
	 * Escribe informacion en la bd. Si @param key ya existe, el nuevo @param value reemplaza al anterior.
	 * No importa el orden de los strings dentro del vector, los mismos strings siempre forman la misma key.
	 */
	void write(vector<string> key, const string& value) override;

	/*
	 * Retorna el value indicado por @param key. Si la key no existe, retorna @param error = true, si existe falso.
	 */
	string read(vector<string> key) const override;

	/**
	 * Devuelve un vector con todas las keys guardadas en la base de datos.
	 */
	std::vector<std::string> getAllKeys() const;

	/*
	 * Borra el @param key con el value asociado de la bd.
	 */
	void erase(vector<string> key);
	/**
	 * Cierra la base de datos
	 */
	void close();
	virtual ~Database();

private:
	/*
	 * Forma una key a partir de un vector de strings.
	 */
	string getKey(vector<string> key) const;
	std::string pathDB;
};

#endif /* DATABASE_H_ */
