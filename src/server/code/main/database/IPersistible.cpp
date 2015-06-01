/*
 * IPersistible.cpp
 *
 *  Created on: Mar 31, 2015
 *      Author: fran
 */

#include "../../include/main/database/IPersistible.h"

IPersistible::IPersistible() {
}

IPersistible::~IPersistible() {
}

string IPersistible::read(vector<string> key) const {
	return "";
}

void IPersistible::write(vector<string> key, const string& value) {
}
