/*
 * LocationManagerTests.cpp
 *
 *  Created on: 2/6/2015
 *      Author: marian
 */

#include "../../include/tests/LocationManagerTests.h"

CPPUNIT_TEST_SUITE_REGISTRATION(LocationManagerTests);

LocationManagerTests::LocationManagerTests() {
}

LocationManagerTests::~LocationManagerTests() {
}

void LocationManagerTests::setUp() {
	TestFixture::setUp();
}

void LocationManagerTests::tearDown() {
	TestFixture::tearDown();
}

void LocationManagerTests::testShouldReturnUnknown() {
	CPPUNIT_ASSERT(LocationManager::getInstance()->getLocation("0;0") == "unknown");
}

void LocationManagerTests::testShouldReturnCABA() {
	CPPUNIT_ASSERT(LocationManager::getInstance()->getLocation("50,50") == "CABA");

}

void LocationManagerTests::testShouldParseAllLocations() {
	CPPUNIT_ASSERT(LocationManager::getInstance()->nodes.size() == 5);
}

void LocationManagerTests::testShouldParseLocation() {
	double lat, lon;
	GeoNode::parseLocation("-34.4569;56.0989", lat, lon);
	CPPUNIT_ASSERT(lat == -34.4569);
	CPPUNIT_ASSERT(lon == 56.0989);
}

void LocationManagerTests::testShouldGetLocation() {

	CPPUNIT_ASSERT(
			LocationManager::getInstance()->getLocation("-34.6217;-58.3724")
					== "San Telmo");
	CPPUNIT_ASSERT(
			LocationManager::getInstance()->getLocation("-34.6183;-58.3790")
					== "San Telmo");
	CPPUNIT_ASSERT(
			LocationManager::getInstance()->getLocation("-34.6179;-58.3691")
					== "San Telmo");

	CPPUNIT_ASSERT(
			LocationManager::getInstance()->getLocation("-34.6101;-58.3704")
					== "Monserrat");
	CPPUNIT_ASSERT(
			LocationManager::getInstance()->getLocation("-34.6115;-58.3747")
					== "Monserrat");

	CPPUNIT_ASSERT(
			LocationManager::getInstance()->getLocation("-34.5890;-58.41")
					== "Palermo");

	CPPUNIT_ASSERT(
			LocationManager::getInstance()->getLocation("-34.6080;-58.3754")
					== "San Nicolas");
	CPPUNIT_ASSERT(
			LocationManager::getInstance()->getLocation("-34.6033;-58.3845")
					== "San Nicolas");

	CPPUNIT_ASSERT(
			LocationManager::getInstance()->getLocation("-34.5911;-58.3767")
					== "Retiro");
	CPPUNIT_ASSERT(
			LocationManager::getInstance()->getLocation("-34.5965;-58.3770")
					== "Retiro");
	CPPUNIT_ASSERT(
			LocationManager::getInstance()->getLocation("-34.5934;-58.3732")
					== "Retiro");
}
