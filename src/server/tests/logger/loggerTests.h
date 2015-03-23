#ifndef CPP_UNIT_EXAMPLETESTCASE_H
#define CPP_UNIT_EXAMPLETESTCASE_H

#include <cppunit/extensions/HelperMacros.h>

class loggerTests: public CPPUNIT_NS::TestFixture {

	CPPUNIT_TEST_SUITE( loggerTests );
	CPPUNIT_TEST(test_suma);
	CPPUNIT_TEST_SUITE_END();

protected:
	void test_suma();
};

#endif
