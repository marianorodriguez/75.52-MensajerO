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


class Database: public IPersistible {
private:
	rocksdb::DB* db;
public:
	Database();
	Database(string path);
	void write(string key, string value) override;
	string read(string key,bool* error) override;
	void erase(string key);
	virtual ~Database();
};

#endif /* DATABASE_H_ */
