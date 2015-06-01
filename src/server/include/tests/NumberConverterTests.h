#ifndef NUMBERCONVERTERTESTS_H
#define NUMBERCONVERTERTESTS_H

#include "cppunit/extensions/HelperMacros.h"

class NumberConverterTests : public CppUnit::TestFixture{
	CPPUNIT_TEST_SUITE(NumberConverterTests);
	CPPUNIT_TEST(testValidNumbers);
	CPPUNIT_TEST(testInvalidNumbers);
	CPPUNIT_TEST(testParseValidNumbers);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	/**
	 * Comprueba una entrada de números válidos
	 */
	void testValidNumbers();
	/**
	 * Comprueba una entrada de números inválidos
	 */
	void testInvalidNumbers();
	/**
	 * Comprueba que parsee números
	 */
	void testParseValidNumbers();
	// TODO mlafroce: Testear números inválidos
};

#endif // NUMBERCONVERTERTESTS_H
