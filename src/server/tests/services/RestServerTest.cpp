#include "RestServerTest.h"
#include "services/ServerThread.h"
#include "services/RestServer.h"
#include "../rest-client/RestClient.h"
#include <cstdio>

CPPUNIT_TEST_SUITE_REGISTRATION(RestServerTest);

RestServerTest::~RestServerTest(){}

void RestServerTest::setUp(){
	printf("SetUp");
    CppUnit::TestFixture::setUp();
}

void RestServerTest::tearDown(){
    CppUnit::TestFixture::tearDown();
}

void RestServerTest::testConstructor(){
	RestServer server;
	server.pollServer();
	server.shutdownServer();
}

void RestServerTest::testEchoReply(){
	ServerThread server;
	server.run();
	RestClient client;
	RestQuery query;
	query.setBaseUri("127.0.0.1:8081/echo");
	query.setParameter("param", "Param");
	client.execute(RestClient::GET, query);
	server.shutdown();
	server.join();
}
