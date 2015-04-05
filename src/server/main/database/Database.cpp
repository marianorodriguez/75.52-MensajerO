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
	rocksdb::Status status = rocksdb::DB::Open(options, path , &database);
}

void Database::write(vector<string> key, string value) {
	rocksdb::Status status = database->Put(rocksdb::WriteOptions(),this->getKey(key),value);
	if(!status.ok()) {
		Logger* logger1 = Logger::getLogger();
		logger1->write(Logger::ERROR,"No se pudo escribir en la base de datos de: " + database->GetName());
	}
}

string Database::read(vector<string> key,bool* error) {
	string value = "";
	rocksdb::Status status = database->Get(rocksdb::ReadOptions(),this->getKey(key),&value);
	if (!status.ok()) {
		*error = true;
	} else {
		*error = false;
	}
	return value;
}

void Database::erase(vector<string> key) {
	string compoundKey = this->getKey(key);
	rocksdb::Status status = database->Delete(rocksdb::WriteOptions(),compoundKey);
	if(!status.ok()) {
		Logger* logger1 = Logger::getLogger();
		logger1->write(Logger::ERROR,"No se pudo borrar la clave '" + compoundKey + "' en la base de datos de: " + database->GetName());
	}
}

string Database::getKey(vector<string> key){
	sort(key.begin(),key.end());
	Json::Value returnKey;
	for (int i = 0; i < key.size();i++){
		returnKey["key"][key[i]] = key[i];
	}
	return returnKey.toStyledString();
}

Database::~Database() {
	delete database;
}

