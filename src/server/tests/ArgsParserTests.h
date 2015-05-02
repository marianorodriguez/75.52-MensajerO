#ifndef ARGSPARSER_TESTS_H
#define ARGSPARSER_TESTS_H

#include "cppunit/extensions/HelperMacros.h"
#include "services/ServerThread.h"

class ArgsParserTests : public CppUnit::TestFixture{
	CPPUNIT_TEST_SUITE(ArgsParserTests);
	CPPUNIT_TEST(testEmptyArgs);
	CPPUNIT_TEST(testValidArgs);
	CPPUNIT_TEST(testLongValidArgs);
	CPPUNIT_TEST(testInvalidArgs);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	/**
	 * Comprueba que genere una salida vacía
	 */
	void testEmptyArgs();
	/**
	 * Comprueba una entrada de parámetros válidos
	 */
	void testValidArgs();
	/**
	 * Comprueba una entrada de parámetros largos válidos
	 */
	void testLongValidArgs();
	/**
	 * Comprueba una entrada de parámetros inválidos
	 */
	void testInvalidArgs();
};

#endif // ARGSPARSER_TESTS_H
