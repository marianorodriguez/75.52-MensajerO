/*
 * Database.h
 *
 *  Created on: Mar 31, 2015
 *      Author: fran
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <rocksdb/db.h>
#include "json/json.h"
#include <iostream>
#include "../interfaces/Persistible/IPersistible.h"
#include "../logger/logger.h"

/*
 * This class defines a database where information is stored as key-value.
 */

class Database: public IPersistible {
private:
	rocksdb::DB* database;
public:
	Database();
	/*
	 * Opens the database in the @param path specified. If database doesn't exist, it creates it.
	 */
	Database(string path);

	/*
	 * Writes information in the database. If @param key already exists, the new @param value replaces the old one.
	 */
	void write(string key, string value) override;

	/*
	 * Returns the value located in @param key. If key doesn't exist, returns @param error = true; false otherwise.
	 */
	string read(string key,bool* error) override;

	/*
	 * Erases the @param key with it's value from the database.
	 */
	void erase(string key);
	virtual ~Database();
};

#endif /* DATABASE_H_ */
