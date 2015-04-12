/*
 * Database.cpp
 *
 *  Created on: Mar 31, 2015
 *      Author: fran
 */

#include "Database.h"

Database::Database() {
	rocksdb::Options options;
	options.create_if_missing = true;
	rocksdb::Status status = rocksdb::DB::Open(options, DEFAULT_DATABASE_PATH , &database);
}

Database::Database(const string& path) {
	rocksdb::Options options;
	options.create_if_missing = true;
	rocksdb::Status status = rocksdb::DB::Open(options, path , &database);
}

void Database::write(vector<string> key, const string& value) {
	string compoundKey = this->getKey(key);
	rocksdb::Status status = database->Put(rocksdb::WriteOptions(),compoundKey,value);
	if(!status.ok()) {
		Logger* logger1 = Logger::getLogger();
		logger1->write(Logger::ERROR,"Hubo un error al escribir en la base de datos de: " + database->GetName() + " la key: " + compoundKey);
	}
}

string Database::read(vector<string> key) const{
	string value = "";
	string compoundKey = this->getKey(key);
	rocksdb::Status status = database->Get(rocksdb::ReadOptions(),compoundKey,&value);
	if (!status.ok()) {
		KeyNotFoundException* e = new KeyNotFoundException("Key no encontrada: " + compoundKey );
		throw *e;
	}
	return value;
}

void Database::erase(vector<string> key) {
	string compoundKey = this->getKey(key);
	rocksdb::Status status = database->Delete(rocksdb::WriteOptions(),compoundKey);
	if(!status.ok()) {
		Logger* logger1 = Logger::getLogger();
		logger1->write(Logger::ERROR,"Hubo un error al borrar de la base de datos de: " + database->GetName() + "la key: " + compoundKey);
	}
}

string Database::getKey(vector<string> key) const{
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

