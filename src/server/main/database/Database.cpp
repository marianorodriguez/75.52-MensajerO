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
	if (!database){
		FileNotFoundException exception("Database file not found");
		throw exception;
	}
}

Database::Database(const string& path) {
	rocksdb::Options options;
	options.create_if_missing = true;
	rocksdb::Status status = rocksdb::DB::Open(options, path , &database);
	if (!database){
		FileNotFoundException exception("Database file not found");
		throw exception;
	}
}

void Database::write(vector<string> key, const string& value) {
	if (key.size() == 0) {
		InvalidKeyException exception("Vector de keys esta vacio.");
		throw exception;
	}
	string compoundKey = this->getKey(key);
	rocksdb::Status status = database->Put(rocksdb::WriteOptions(),compoundKey,value);
	if(!status.ok()) {
		InvalidKeyException exception("Invalid key.");
		Logger* logger1 = Logger::getLogger();
		logger1->write(Logger::ERROR, "Error: " + status.ToString() + " Hubo un error al escribir en la base de datos de: " + database->GetName() + " la key: " + compoundKey);
	}
}

string Database::read(vector<string> key) const{
	if (key.size() == 0) {
		InvalidKeyException exception("Vector de keys esta vacio.");
		throw exception;
	}
	string value = "";
	string compoundKey = this->getKey(key);
	rocksdb::Status status = database->Get(rocksdb::ReadOptions(),compoundKey,&value);
	if (!status.ok()) {
		KeyNotFoundException exception("Key no encontrada: " + compoundKey );
		throw exception;
	}
	return value;
}

void Database::erase(vector<string> key) {
	string compoundKey = this->getKey(key);
	rocksdb::Status status = database->Delete(rocksdb::WriteOptions(),compoundKey);
	if(!status.ok()) {
		Logger* logger1 = Logger::getLogger();
		logger1->write(Logger::ERROR,"Error: " + status.ToString() + " Hubo un error al borrar de la base de datos de: " + database->GetName() + "la key: " + compoundKey);
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

void Database::close(){
	delete database;
	database = 0;
}


Database::~Database() {
	close();
}

