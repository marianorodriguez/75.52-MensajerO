#include "RestServerTest.h"
#include "services/RestServer.h"
#include "../rest-client/RestClient.h"

CPPUNIT_TEST_SUITE_REGISTRATION(RestServerTest);

RestServerTest::~RestServerTest(){}

void RestServerTest::setUp(){
	CppUnit::TestFixture::setUp();
	this->testServer = new ServerThread();
	this->testServer->run();
}

void RestServerTest::tearDown(){
    CppUnit::TestFixture::tearDown();
	this->testServer->shutdown();
	this->testServer->join();
	delete this->testServer;
}

void RestServerTest::testConstructor(){
	RestServer server;
	server.pollServer();
	server.shutdownServer();
}

void RestServerTest::testEchoReply(){
	RestClient client;
	RestQuery query;
	query.setBaseUri("127.0.0.1:8081/echo");
	query.setParameter("param", "Param");
	std::string response;
	response = client.execute(RestClient::GET, query);
	CPPUNIT_ASSERT(!response.empty());
	CPPUNIT_ASSERT(response.find("echo") != std::string::npos);
	CPPUNIT_ASSERT(response.find("param") != std::string::npos);
	CPPUNIT_ASSERT(response.find("Param") != std::string::npos);
}
