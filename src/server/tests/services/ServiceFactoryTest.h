#ifndef SERVICE_FACTORY_TEST_H
#define SERVICE_FACTORY_TEST_H

#include "cppunit/extensions/HelperMacros.h"
#include "services/ServiceFactory.h"
#include "services/EchoService.h"

/**
 * Tests sobre la colección de servicios
 */
class ServiceFactoryTest : public CppUnit::TestFixture{
	CPPUNIT_TEST_SUITE(ServiceFactoryTest);
	CPPUNIT_TEST(testGetService);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	/**
	 * Compruebo que se puedan agregar servicios a la colección
	 */
	void testGetService();
private:
	ServiceFactory serviceFactory;
};

#endif // SERVICE_FACTORY_TEST_H
