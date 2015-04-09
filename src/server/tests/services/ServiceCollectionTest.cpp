#include <cstdio>

#include "ServiceCollectionTest.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ServiceCollectionTest);

void ServiceCollectionTest::setUp(){}

void ServiceCollectionTest::tearDown(){}

void ServiceCollectionTest::testAddService(){
	ServiceInterface* echoService = new EchoService();
	this->serviceCollection.addService(echoService);
	std::vector<std::string> serviceNameList;
	serviceNameList = serviceCollection.getServiceNameList();
	int listSize = serviceNameList.size();
	CPPUNIT_ASSERT_EQUAL(1, listSize);
	std::string echoServiceName(echoService->getUri());
	// Me fijo que el nombre del servicio devuelto sea el del que almacené
	CPPUNIT_ASSERT(echoServiceName.compare(serviceNameList[0]) == 0);
}