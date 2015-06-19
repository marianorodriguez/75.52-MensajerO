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
		string message = "Database file not found.";
		FileNotFoundException exception(message);
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
		string message = "Database file not found.";
		FileNotFoundException exception(message);
		throw exception;
	}
}

void Database::write(vector<string> key, const string& value) {
	if (key.size() == 0) {
		InvalidKeyException exception("Null key.");
		throw exception;
	}
	string compoundKey = this->getKey(key);
	rocksdb::Status status = database->Put(rocksdb::WriteOptions(), compoundKey,value);
	if (!status.ok()) {
		InvalidKeyException exception(status.ToString() + ": Invalid key.");
		throw exception;
	}
	Logger::getLogger()->write(Logger::DEBUG, "Key saved in database.");
}

string Database::read(vector<string> key) const {
	if (key.size() == 0) {
		InvalidKeyException exception("Null key.");
		throw exception;
	}
	string value = "";
	string compoundKey = this->getKey(key);
	rocksdb::Status status = database->Get(rocksdb::ReadOptions(), compoundKey,	&value);
	if (!status.ok()) {
		string message = "Key not found in database: " + compoundKey;
		KeyNotFoundException exception(message);
		throw exception;
	}
	return value;
}

void Database::erase(vector<string> key) {
	string compoundKey = this->getKey(key);
	rocksdb::Status status = database->Delete(rocksdb::WriteOptions(),
			compoundKey);
	if (!status.ok()) {
		Logger::getLogger()->write(Logger::WARN, status.ToString() + ": couldn't erase a key from the database");
	}
	Logger::getLogger()->write(Logger::DEBUG, "Key deleted from database.");

}

string Database::getKey(vector<string> key) const {
	sort(key.begin(), key.end());
	Json::Value returnKey;
	for (unsigned int i = 0; i < key.size(); i++) {
		returnKey.append(key[i]);
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
		Logger::getLogger()->write(Logger::WARN, "Error found during the scan of " + database->GetName());
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
