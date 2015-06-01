#ifndef RESTCLIENTTEST_H
#define RESTCLIENTTEST_H

#include "cppunit/extensions/HelperMacros.h"
#include "../../include/main/services/ServerThread.h"

class RestClientTest : public CppUnit::TestFixture{
	CPPUNIT_TEST_SUITE(RestClientTest);
	CPPUNIT_TEST(testBuildQuery);
	CPPUNIT_TEST(testGet);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	/**
	 * Comprueba que se arme bien el query
	 */
	void testBuildQuery();
	/**
	 * Comprueba que realice un get correctamente
	 */
	void testGet();

	void testPost();
};

#endif // RESTCLIENTTEST_H
