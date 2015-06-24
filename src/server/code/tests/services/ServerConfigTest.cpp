
#include "services/ServerConfigTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ServerConfigTest);

ServerConfigTest::~ServerConfigTest() {
}

void ServerConfigTest::setUp() {
	CppUnit::TestFixture::setUp();

}

void ServerConfigTest::tearDown() {
	CppUnit::TestFixture::tearDown();
}

void ServerConfigTest::testShouldConfigure(){
	OptionMap map;
	map["database"] = "database/test";
	map["port"] = "9000";
	map["pollDelay"] = "1000";
	map["aliveTime"] = "4000";
	ServerOptions options(map);

	ServerConfig config(options);
	RestServer server;
	config.configure(server);

	CPPUNIT_ASSERT(server.pollDelay == 1000);
	CPPUNIT_ASSERT(server.port == 9000);
	CPPUNIT_ASSERT(server.userDbPath == "database/test/users");
	CPPUNIT_ASSERT(server.chatDbPath == "database/test/chats");
}
