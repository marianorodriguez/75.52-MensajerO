/*
 * Base64Tests.h
 *
 *  Created on: 24/6/2015
 *      Author: marian
 */

#ifndef CODE_TESTS_BASE64TESTS_H_
#define CODE_TESTS_BASE64TESTS_H_

#include <cppunit/extensions/HelperMacros.h>
#include "../../include/main/utilities/Base64.h"

class Base64Tests: public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(Base64Tests);
	CPPUNIT_TEST(testShouldEncode);
	CPPUNIT_TEST(testShouldDecode);
	CPPUNIT_TEST_SUITE_END();

public:
	Base64Tests();
	virtual ~Base64Tests();

	void testShouldEncode();
	void testShouldDecode();

};

#endif /* CODE_TESTS_BASE64TESTS_H_ */
