#include "ServiceFactoryTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ServiceFactoryTest);

void ServiceFactoryTest::setUp(){
	CppUnit::TestFixture::setUp();
}

void ServiceFactoryTest::tearDown(){
	CppUnit::TestFixture::tearDown();
}

void ServiceFactoryTest::testGetService(){
	ServiceInterface* service;
	// Compruebo que me devuelva un servicio con nombre válido
	service = this->serviceFactory.createService("createUser");
	std::string uri(service->getUri());
	CPPUNIT_ASSERT(uri.compare("createUser") == 0);
	delete service;
	// Devuelve una instancia de NullService
	service = this->serviceFactory.createService("im an invalid service");
	uri.assign(service->getUri());
	CPPUNIT_ASSERT(uri.compare("") == 0);
}