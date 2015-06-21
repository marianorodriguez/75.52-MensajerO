#include "../../include/tests/services/ServiceFactoryTest.h"
#include "../../include/tests/services/EchoService.h"
#include "../../include/main/services/ServiceInterface.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ServiceFactoryTest);

void ServiceFactoryTest::setUp(){
	CppUnit::TestFixture::setUp();
}

void ServiceFactoryTest::tearDown(){
	CppUnit::TestFixture::tearDown();
}

void ServiceFactoryTest::testGetService(){
	Database fooDb;
	ServiceFactory serviceFactory(fooDb, fooDb);
	serviceFactory.addNewServiceCreator(new EchoServiceCreator());
	ServiceInterface* service;
	// Compruebo que me devuelva un servicio con nombre válido
	service = serviceFactory.createService("echo");
	std::string uri(service->getUri());
	CPPUNIT_ASSERT(uri.compare("echo") == 0);
	delete service;
	// Devuelve una instancia de NullService
	service = serviceFactory.createService("im an invalid service");
	uri.assign(service->getUri());
	CPPUNIT_ASSERT(uri.compare("") == 0);
	delete service;
}
