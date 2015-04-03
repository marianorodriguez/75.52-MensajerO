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
	rocksdb::Status status = db->Put(rocksdb::WriteOptions(),key,value);
	if(!status.ok()) {
		logger* logger1 = logger::getLogger();
		logger1->write(logger::ERROR,"No se pudo escribir en la base de datos de: " + db->GetName());
	}
}

string Database::read(string key,bool* error) {
	string value = "";
	rocksdb::Status status = db->Get(rocksdb::ReadOptions(),key,&value);
	if (!status.ok()) {
		*error = true;
	} else {
		*error = false;
	}
	return value;
}

void Database::erase(string key) {
	rocksdb::Status status = db->Delete(rocksdb::WriteOptions(),key);
	if(!status.ok()) {
		logger* logger1 = logger::getLogger();
		logger1->write(logger::ERROR,"No se pudo borrar la clave '" + key + "' en la base de datos de: " + db->GetName());
	}
}

Database::~Database() {
	delete db;
}

