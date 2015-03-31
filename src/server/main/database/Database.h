/*
 * Database.h
 *
 *  Created on: Mar 31, 2015
 *      Author: fran
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <rocksdb/db.h>
#include <iostream>

using namespace std;

class Database {
private:
	rocksdb::DB* db;
public:
	Database();
	Database(string path);
	void write(string key, string value);
	string read(string key,bool* error);
	void erase(string key);
	virtual ~Database();
};

#endif /* DATABASE_H_ */
