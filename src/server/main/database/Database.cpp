/*
 * Database.cpp
 *
 *  Created on: Mar 31, 2015
 *      Author: fran
 */

#include "Database.h"

Database::Database() { }

Database::Database(string path) {
	rocksdb::Options options;
	options.create_if_missing = true;
	rocksdb::Status status = rocksdb::DB::Open(options, path , &db);
}

void Database::write(string key, string value) {
	db->Put(rocksdb::WriteOptions(),key,value);
}

string Database::read(string key,bool* error) {
	string value = "";
	rocksdb::Status status = db->Get(rocksdb::ReadOptions(),key,&value);
	if (!status.ok()) {
		*error = true;
	} else {
		error = false;
	}
	return value;
}

void Database::erase(string key) {
	db->Delete(rocksdb::WriteOptions(),key);
	string serialized;
	Json::Value parsed;
	Json::Reader reader;
}

Database::~Database() {
	delete db;
}

