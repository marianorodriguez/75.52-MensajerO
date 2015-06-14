#include "../../include/tests/services/RestServerTest.h"
#include "../../include/tests/services/EchoService.h"
#include "../../include/main/services/RestServer.h"
#include "../../include/tests/rest-client/RestClient.h"

CPPUNIT_TEST_SUITE_REGISTRATION(RestServerTest);

RestServerTest::~RestServerTest(){}

void RestServerTest::setUp(){
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
	// Instancio servidor
	this->testServer = new ServerThread();
	this->testServer->addService(new EchoServiceCreator());
	this->testServer->run();
	// Creo cliente
	RestClient client;
	RestQuery query;
	query.setBaseUri("127.0.0.1:8081/echo");
	query.setParameter("param1", "foo");
	query.setParameter("param2", "bar");
	std::string response;
	response = client.execute(RestClient::GET, query);
	CPPUNIT_ASSERT(!response.empty());
	CPPUNIT_ASSERT(response.find("echo") != std::string::npos);
	CPPUNIT_ASSERT(response.find("param1") != std::string::npos);
	CPPUNIT_ASSERT(response.find("foo") != std::string::npos);
	// apago servidor y uno thread
	this->testServer->shutdown();
	this->testServer->join();
	delete this->testServer;
}
