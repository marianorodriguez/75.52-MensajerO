/*
 * ServerOptionsTests.h
 *
 *  Created on: 23/6/2015
 *      Author: marian
 */

#ifndef INCLUDE_TESTS_SERVEROPTIONSTESTS_H_
#define INCLUDE_TESTS_SERVEROPTIONSTESTS_H_

#include "cppunit/extensions/HelperMacros.h"
#include "../../include/main/ServerOptions.h"

class ServerOptionsTests : public CppUnit::TestFixture{
	CPPUNIT_TEST_SUITE(ServerOptionsTests);
	CPPUNIT_TEST(testShouldNotFindConfigFile);
	CPPUNIT_TEST(testDefaultOptions);
	CPPUNIT_TEST(testCustomOptions);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testShouldNotFindConfigFile();
	void testDefaultOptions();
	void testCustomOptions();
};

#endif /* INCLUDE_TESTS_SERVEROPTIONSTESTS_H_ */
