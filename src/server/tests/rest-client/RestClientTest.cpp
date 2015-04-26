#include "RestClientTest.h"
#include "RestClient.h"
#include "../services/EchoService.h"

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
