/*
 * Database.cpp
 *
 *  Created on: Mar 31, 2015
 *      Author: fran
 */

#include "../../include/main/database/Database.h"
#include "json.h"

Database::Database() :
		database(NULL) {
	open(DEFAULT_DATABASE_PATH);
}

Database::Database(const string& path) :
		database(NULL) {
	open(path);
}

void Database::write(const std::vector<std::string>& key, const string& value) {
	if (key.size() == 0) {
		InvalidKeyException exception("Null key.");
		throw exception;
	}
	std::string compoundKey = this->getKey(key);
	rocksdb::Status status = database->Put(rocksdb::WriteOptions(), compoundKey,
			value);

	if (!status.ok()) {
		InvalidKeyException exception("Invalid key.");
		Logger* logger1 = Logger::getLogger();
		logger1->write(Logger::ERROR,
				"Error: " + status.ToString()
						+ " Hubo un error al escribir en la base de datos de: "
						+ database->GetName() + " la key: " + compoundKey);
		throw exception;
	}
}

string Database::read(const std::vector<std::string>& key) const {
	if (key.size() == 0) {
		InvalidKeyException exception("Null key.");
		throw exception;
	}
	string value = "";
	string compoundKey = this->getKey(key);
	rocksdb::Status status = database->Get(rocksdb::ReadOptions(), compoundKey,
			&value);
	if (!status.ok()) {
		string message = "Key " + compoundKey + " not found in database.";
		throw KeyNotFoundException(message);
	}
	return value;
}

void Database::erase(const std::vector<std::string>& key) {
	string compoundKey = this->getKey(key);
	rocksdb::Status status = database->Delete(rocksdb::WriteOptions(),
			compoundKey);
	if (!status.ok()) {
		Logger::getLogger()->write(Logger::WARN,
				status.ToString() + ": couldn't erase a key from the database");
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
		reader.parse(it->key().ToString(), value);
		string str(value[0].toStyledString());
		str.erase(0, 1);
		str.erase(str.size() - 2, string::npos);
		keys.push_back(str);
	}
	if (!it->status().ok()) { // Check for any errors found during the scan
		Logger::getLogger()->write(Logger::WARN,
				"Error found during the scan of " + database->GetName());
	}
	delete it;

	return keys;
}

void Database::open(const string& path) {
	close();
	database = NULL;
	rocksdb::Options options;
	options.create_if_missing = true;
	rocksdb::Status status = rocksdb::DB::Open(options, path, &database);
	pathDB = path;

	if (!database) {
		std::string message = "Database file not found.";
		FileNotFoundException exception(message);
		throw exception;
	}
}

void Database::close() {
	delete database;
	database = NULL;
}

Database::~Database() {
	close();
}
