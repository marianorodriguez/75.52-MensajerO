#ifndef SERVICECOLLECTIONTEST_H
#define SERVICECOLLECTIONTEST_H

#include "cppunit/extensions/HelperMacros.h"
#include "services/ServiceCollection.h"
#include "EchoService.h"

/**
 * Tests sobre la colección de servicios
 */
class ServiceCollectionTest : public CppUnit::TestFixture{
	CPPUNIT_TEST_SUITE(ServiceCollectionTest);
	CPPUNIT_TEST(testAddService);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	/**
	 * Compruebo que se puedan agregar servicios a la colección
	 */
	void testAddService();
private:
	ServiceCollection serviceCollection;
};

#endif // SERVICECOLLECTIONTEST_H
