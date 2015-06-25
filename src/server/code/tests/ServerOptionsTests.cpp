/*
 * ServerOptionsTests.cpp
 *
 *  Created on: 23/6/2015
 *      Author: marian
 */

#include "../../include/tests/ServerOptionsTests.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ServerOptionsTests);

void ServerOptionsTests::setUp(){
	CppUnit::TestFixture::setUp();

}

void ServerOptionsTests::tearDown(){
	CppUnit::TestFixture::tearDown();

}

void ServerOptionsTests::testShouldNotFindConfigFile(){

	OptionMap map;
	map["config"] = "invalidConfigPath";
	ServerOptions options(map);
	CPPUNIT_ASSERT(options.getConfigPath() == "config/config.json");
	CPPUNIT_ASSERT(options.getDatabasePath() == "database");
	CPPUNIT_ASSERT(options.getPollDelay() == 1000);
	CPPUNIT_ASSERT(options.getServerPort() == 8081);
	CPPUNIT_ASSERT(options.getUserAliveTime() == 2000);
}

void ServerOptionsTests::testDefaultOptions(){

	ServerOptions options;
	CPPUNIT_ASSERT(options.getConfigPath() == "config/config.json");
	CPPUNIT_ASSERT(options.getDatabasePath() == "database");
	CPPUNIT_ASSERT(options.getPollDelay() == 1000);
	CPPUNIT_ASSERT(options.getServerPort() == 8081);
	CPPUNIT_ASSERT(options.getUserAliveTime() == 2000);
}

void ServerOptionsTests::testCustomOptions(){

	OptionMap map;
	map["database"] = "newDatabasePath";
	map["port"] = "9000";
	map["pollDelay"] = "1000";
	map["aliveTime"] = "4000";
	ServerOptions options(map);

	CPPUNIT_ASSERT(options.getDatabasePath() == "newDatabasePath");
	CPPUNIT_ASSERT(options.getPollDelay() == 1000);
	CPPUNIT_ASSERT(options.getServerPort() == 9000);
	CPPUNIT_ASSERT(options.getUserAliveTime() == 4000);
}
