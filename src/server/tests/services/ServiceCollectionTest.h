#ifndef SERVICECOLLECTIONTEST_H
#define SERVICECOLLECTIONTEST_H

#include "cppunit/extensions/HelperMacros.h"
#include "services/ServiceCollection.h"

class ServiceCollectionTest : public CppUnit::TestFixture{
	CPPUNIT_TEST_SUITE(ServiceCollectionTest);
	CPPUNIT_TEST(testAddService);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	void testAddService();
private:
	ServiceCollection servCollection;
};

#endif // SERVICECOLLECTIONTEST_H
