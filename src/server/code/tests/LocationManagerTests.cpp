/*
 * LocationManagerTests.cpp
 *
 *  Created on: 2/6/2015
 *      Author: marian
 */

#include "../../include/tests/LocationManagerTests.h"

CPPUNIT_TEST_SUITE_REGISTRATION(LocationManagerTests);

LocationManagerTests::LocationManagerTests() {
	this->lm = 0;
}

LocationManagerTests::~LocationManagerTests() {
}

void LocationManagerTests::setUp() {
	TestFixture::setUp();
	this->lm = new LocationManager();
}

void LocationManagerTests::tearDown() {
	TestFixture::tearDown();
	delete this->lm;
}

void LocationManagerTests::testShouldParseAllLocations() {
	CPPUNIT_ASSERT(this->lm->nodes.size() == 5);
}

void LocationManagerTests::testShouldParseLocation() {
	double lat, lon;
	GeoNode::parseLocation("-34.4569;56.0989", lat, lon);
	CPPUNIT_ASSERT(lat == -34.4569);
	CPPUNIT_ASSERT(lon == 56.0989);
}

void LocationManagerTests::testShouldGetLocation() {

	CPPUNIT_ASSERT(lm->getLocation("-34.6217;-58.3724") == "San Telmo");
	CPPUNIT_ASSERT(lm->getLocation("-34.6183;-58.3790") == "San Telmo");
	CPPUNIT_ASSERT(lm->getLocation("-34.6179;-58.3691") == "San Telmo");

	CPPUNIT_ASSERT(lm->getLocation("-34.6101;-58.3704") == "Monserrat");
	CPPUNIT_ASSERT(lm->getLocation("-34.6115;-58.3747") == "Monserrat");

	CPPUNIT_ASSERT(lm->getLocation("-34.5890;-58.41") == "Palermo");

	CPPUNIT_ASSERT(lm->getLocation("-34.6080;-58.3754") == "San Nicolas");
	CPPUNIT_ASSERT(lm->getLocation("-34.6033;-58.3845") == "San Nicolas");

	CPPUNIT_ASSERT(lm->getLocation("-34.5911;-58.3767") == "Retiro");
	CPPUNIT_ASSERT(lm->getLocation("-34.5965;-58.3770") == "Retiro");
	CPPUNIT_ASSERT(lm->getLocation("-34.5934;-58.3732") == "Retiro");
}
