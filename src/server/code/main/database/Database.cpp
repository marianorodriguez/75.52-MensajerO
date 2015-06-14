/*
 * Database.cpp
 *
 *  Created on: Mar 31, 2015
 *      Author: fran
 */

#include "../../include/main/database/Database.h"

Database::Database() {
	rocksdb::Options options;
	options.create_if_missing = true;
	rocksdb::Status status = rocksdb::DB::Open(options, DEFAULT_DATABASE_PATH,
			&database);
	if (!database) {
		FileNotFoundException exception("Database file not found");
		throw exception;
	}

	pathDB = DEFAULT_DATABASE_PATH;
}

Database::Database(const string& path) {
	rocksdb::Options options;
	options.create_if_missing = true;
	rocksdb::Status status = rocksdb::DB::Open(options, path, &database);
	pathDB = path;
	if (!database) {
		FileNotFoundException exception("Database file not found");
		throw exception;
	}
}

void Database::write(const std::vector<std::string>& key, const string& value) {
	if (key.size() == 0) {
		InvalidKeyException exception("Vector de keys esta vacio.");
		throw exception;
	}
	string compoundKey = this->getKey(key);
	rocksdb::Status status = database->Put(rocksdb::WriteOptions(), compoundKey,value);
	if (!status.ok()) {
		InvalidKeyException exception("Invalid key.");
		Logger* logger1 = Logger::getLogger();
		logger1->write(Logger::ERROR, "Error: " + status.ToString() +
					" Hubo un error al escribir en la base de datos de: " +
					database->GetName() + " la key: " + compoundKey);
	}
}

string Database::read(const std::vector<std::string>& key) const {
	if (key.size() == 0) {
		InvalidKeyException exception("Vector de keys esta vacio.");
		throw exception;
	}
	string value = "";
	string compoundKey = this->getKey(key);
	rocksdb::Status status = database->Get(rocksdb::ReadOptions(), compoundKey,	&value);
	if (!status.ok()) {
		KeyNotFoundException exception("Key no encontrada: " + compoundKey);
		throw exception;
	}
	return value;
}

void Database::erase(const std::vector<std::string>& key) {
	string compoundKey = this->getKey(key);
	rocksdb::Status status = database->Delete(rocksdb::WriteOptions(),
			compoundKey);
	if (!status.ok()) {
		Logger* logger1 = Logger::getLogger();
		logger1->write(Logger::ERROR,
				"Error: " + status.ToString()	+ " Hubo un error al borrar de la base de datos de: "
						+ database->GetName() + "la key: " + compoundKey);
	}
}

string Database::getKey(const std::vector<std::string>& key) const {
	std::vector<std::string> sortedKey = key;
	sort(sortedKey.begin(), sortedKey.end());
	Json::Value returnKey;
	for (unsigned int i = 0; i < sortedKey.size(); i++) {
		returnKey.append(sortedKey.at(i));
	}
	return returnKey.toStyledString();
}

vector<string> Database::getAllKeys() const {

	vector<string> keys;

	rocksdb::Iterator* it = this->database->NewIterator(rocksdb::ReadOptions());
	for (it->SeekToFirst(); it->Valid(); it->Next()) {
		Json::Value value;
		Json::Reader reader;
		reader.parse(it->key().ToString(),value);
		string str (value[0].toStyledString());
		str.erase (0, 1);
		str.erase (str.size()-2,string::npos);
		keys.push_back(str);
	}
	if (!it->status().ok()) {// Check for any errors found during the scan
		Logger* logger1 = Logger::getLogger();
		logger1->write(Logger::ERROR, "Error: Hubo un error al scannear la base de datos de: " + database->GetName());
	}
	delete it;

	return keys;
}

void Database::close() {
	delete database;
	database = NULL;
}

Database::~Database() {
	close();
}
