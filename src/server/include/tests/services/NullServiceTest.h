
#ifndef SERVER_TESTS_SERVICES_NULLSERVICETEST_H_
#define SERVER_TESTS_SERVICES_NULLSERVICETEST_H_

#include "ServiceTest.h"
#include "../../main/services/NullService.h"

class NullServiceTest: public ServiceTest {

	CPPUNIT_TEST_SUITE(NullServiceTest);
	CPPUNIT_TEST(testShouldGetUri);
	CPPUNIT_TEST(testdoNothing);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual ~NullServiceTest();

	void setUp();
	void tearDown();

	void testdoNothing();
	void testShouldGetUri();

};

#endif /* SERVER_TESTS_SERVICES_NULLSERVICETEST_H_ */
