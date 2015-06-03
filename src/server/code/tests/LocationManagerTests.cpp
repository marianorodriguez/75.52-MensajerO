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
	this->lm = new LocationManager();
}

void LocationManagerTests::tearDown() {
	TestFixture::tearDown();
	delete this->lm;
}

void LocationManagerTests::testShouldReturnNodesName() {
	CPPUNIT_ASSERT(lm->nodes["-34.620556;-58.371667"] == "San Telmo");
	CPPUNIT_ASSERT(lm->nodes["-34.612500;-58.383333"] == "Monserrat");
	CPPUNIT_ASSERT(lm->nodes["-34.610426;-58.361707"] == "Puerto Madero");
	CPPUNIT_ASSERT(lm->nodes["-34.605278;-58.375833"] == "San Nicolas");
	CPPUNIT_ASSERT(lm->nodes["-34.594722;-58.375833"] == "Retiro");
}

void LocationManagerTests::testShouldParseLocation() {
	double lat, lon;
	lm->parseLocation("-34.456;56.098", lat, lon);
	CPPUNIT_ASSERT(lat == -34.456);
	CPPUNIT_ASSERT(lon == 56.098);
}

void LocationManagerTests::testShouldReturnNearestLocation() {

	CPPUNIT_ASSERT(lm->nearestNode("-34.620556;-58.371667") == "-34.620556;-58.371667");
	CPPUNIT_ASSERT(lm->nearestNode("-34.620454;-58.371667") == "-34.620556;-58.371667");
	CPPUNIT_ASSERT(lm->nearestNode("-34.612500;-58.383333") == "-34.612500;-58.383333");
	CPPUNIT_ASSERT(lm->nearestNode("-34.610426;-58.361707") == "-34.610426;-58.361707");
	CPPUNIT_ASSERT(lm->nearestNode("-34.605278;-58.375833") == "-34.605278;-58.375833");
	CPPUNIT_ASSERT(lm->nearestNode("-34.605278;-58.375933") == "-34.605278;-58.375833");
	CPPUNIT_ASSERT(lm->nearestNode("-34.594722;-58.375833") == "-34.594722;-58.375833");
}

void LocationManagerTests::testShouldGetLocation() {

	CPPUNIT_ASSERT(lm->getLocation("-34.620556;-58.371667") == "San Telmo");
	CPPUNIT_ASSERT(lm->getLocation("-34.620454;-58.371667") == "San Telmo");
	CPPUNIT_ASSERT(lm->getLocation("-34.612500;-58.383333") == "Monserrat");
	CPPUNIT_ASSERT(lm->getLocation("-34.610426;-58.361707") == "Puerto Madero");
	CPPUNIT_ASSERT(lm->getLocation("-34.605278;-58.375833") == "San Nicolas");
	CPPUNIT_ASSERT(lm->getLocation("-34.605278;-58.375933") == "San Nicolas");
	CPPUNIT_ASSERT(lm->getLocation("-34.594722;-58.375833") == "Retiro");

}
