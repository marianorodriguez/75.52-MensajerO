/*
 * ServiceTest.cpp
 *
 *  Created on: 23/6/2015
 *      Author: marian
 */

#include "../../../include/tests/services/ServiceTest.h"


ServiceTest::~ServiceTest() {}

void ServiceTest::setUp(){
	CppUnit::TestFixture::setUp();

	this->chatDB = new Database("database/test/testServices/chats");
	this->userDB = new Database("database/test/testServices/users");
}

void ServiceTest::tearDown(){
	CppUnit::TestFixture::tearDown();

	delete this->chatDB;
	delete this->userDB;
}
