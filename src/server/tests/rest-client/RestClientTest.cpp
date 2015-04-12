#include "RestClientTest.h"
#include "RestClient.h"

CPPUNIT_TEST_SUITE_REGISTRATION(RestClientTest);

void RestClientTest::setUp(){
    CppUnit::TestFixture::setUp();
}

void RestClientTest::tearDown(){
    CppUnit::TestFixture::tearDown();
}

void RestClientTest::testBuildQuery(){
	RestQuery query;
	query.setBaseUri("http://www.google.com/");
	//Pruebo un único parámetro
	query.setParameter("Param1", "ParamValue");
	std::string queryString = query.buildGetQuery();
	CPPUNIT_ASSERT(queryString.compare("http://www.google.com/?Param1=ParamValue") == 0);
	//Pruebo más parámetros
	query.setParameter("Param2", "OtherValue");
	queryString = query.buildGetQuery();
	CPPUNIT_ASSERT(queryString.compare(
		"http://www.google.com/?Param1=ParamValue&Param2=OtherValue") == 0);
}

void RestClientTest::testGet(){
	RestClient client;
	RestQuery query;
	query.setBaseUri("http://www.google.com/");
	std::string response = client.execute(RestClient::GET, query);
	CPPUNIT_ASSERT(!response.empty());
}

void RestClientTest::testPost(){
	ServerThread server;
	server.run();

	RestClient client;
	RestQuery query;
	query.setBaseUri("http://127.0.0.1:8081/echo");
	query.setPostData("i'm posting some data");
	std::string response = client.execute(RestClient::POST, query);

	CPPUNIT_ASSERT(!response.empty());

	server.shutdown();
	server.join();
}
