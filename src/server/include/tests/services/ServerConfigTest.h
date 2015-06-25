
#ifndef SERVER_TESTS_SERVICES_SERVERCONFIGTEST_H_
#define SERVER_TESTS_SERVICES_SERVERCONFIGTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include "../../main/services/ServerConfig.h"

class ServerConfigTest: public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(ServerConfigTest);
	CPPUNIT_TEST(testShouldConfigure);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual ~ServerConfigTest();

	void setUp();
	void tearDown();

	void testShouldConfigure();
};

#endif /* SERVER_TESTS_SERVICES_SERVERCONFIGTEST_H_ */
