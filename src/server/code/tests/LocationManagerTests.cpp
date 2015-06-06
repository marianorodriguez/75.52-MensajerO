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

void LocationManagerTests::testShouldParseAllLocations(){
	CPPUNIT_ASSERT(this->lm->nodes.size() == 39);
}

void LocationManagerTests::testShouldReturnNodesName() {
	CPPUNIT_ASSERT(lm->nodes["-34.6227;-58.3829"] == "Constitucion");
	CPPUNIT_ASSERT(lm->nodes["-34.6261;-58.3773"] == "San Telmo");
	CPPUNIT_ASSERT(lm->nodes["-34.6175;-58.3886"] == "Monserrat");
	CPPUNIT_ASSERT(lm->nodes["-34.6192;-58.3675"] == "Puerto Madero");
	CPPUNIT_ASSERT(lm->nodes["-34.6080;-58.3847"] == "San Nicolas");
	CPPUNIT_ASSERT(lm->nodes["-34.5960;-58.3848"] == "Retiro");
}

void LocationManagerTests::testShouldParseLocation() {
	double lat, lon;
	lm->parseLocation("-34.4569;56.0989", lat, lon);
	CPPUNIT_ASSERT(lat == -34.4569);
	CPPUNIT_ASSERT(lon == 56.0989);
}

void LocationManagerTests::testShouldGetLocation() {

	CPPUNIT_ASSERT(lm->getLocation("-34.6300;-58.3875") == "Constitucion");
	CPPUNIT_ASSERT(lm->getLocation("-34.6240;-58.3850") == "Constitucion");

	CPPUNIT_ASSERT(lm->getLocation("-34.6217;-58.3724") == "San Telmo");
	CPPUNIT_ASSERT(lm->getLocation("-34.6183;-58.3790") == "San Telmo");

	CPPUNIT_ASSERT(lm->getLocation("-34.6191;-58.3904") == "Monserrat");
	CPPUNIT_ASSERT(lm->getLocation("-34.6115;-58.3747") == "Monserrat");

	CPPUNIT_ASSERT(lm->getLocation("-34.6230;-58.3686") == "Puerto Madero");
	CPPUNIT_ASSERT(lm->getLocation("-34.6135;-58.3715") == "Puerto Madero");

	CPPUNIT_ASSERT(lm->getLocation("-34.6090;-58.3754") == "San Nicolas");
	CPPUNIT_ASSERT(lm->getLocation("-34.6033;-58.3845") == "San Nicolas");

	CPPUNIT_ASSERT(lm->getLocation("-34.6011;-58.3867") == "Retiro");
	CPPUNIT_ASSERT(lm->getLocation("-34.5995;-58.3770") == "Retiro");
	CPPUNIT_ASSERT(lm->getLocation("-34.5904;-58.3732") == "Retiro");
}
