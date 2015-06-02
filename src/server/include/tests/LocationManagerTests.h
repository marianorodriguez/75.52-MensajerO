/*
 * LocationManagerTests.h
 *
 *  Created on: 2/6/2015
 *      Author: marian
 */

#ifndef CODE_TESTS_LOCATIONMANAGERTESTS_H_
#define CODE_TESTS_LOCATIONMANAGERTESTS_H_

#include "../../include/main/utilities/LocationManager.h"
#include "cppunit/extensions/HelperMacros.h"

class LocationManagerTests: public CppUnit::TestFixture {

CPPUNIT_TEST_SUITE(LocationManagerTests);
	CPPUNIT_TEST(testShouldReturnNodesName);
	CPPUNIT_TEST(testShouldParseLocation);
	CPPUNIT_TEST(testShouldReturnNearestLocation);
	CPPUNIT_TEST(testShouldGetLocation);
	CPPUNIT_TEST_SUITE_END();

public:
	LocationManagerTests();
	virtual ~LocationManagerTests();

	void setUp();
	void tearDown();

	void testShouldReturnNodesName();
	void testShouldParseLocation();
	void testShouldReturnNearestLocation();
	void testShouldGetLocation();

private:
	LocationManager* lm;
};

#endif /* CODE_TESTS_LOCATIONMANAGERTESTS_H_ */
