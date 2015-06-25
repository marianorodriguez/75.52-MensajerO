/*
 * Base64Tests.cpp
 *
 *  Created on: 24/6/2015
 *      Author: marian
 */

#include "Base64Tests.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Base64Tests);

Base64Tests::Base64Tests() {
}

Base64Tests::~Base64Tests() {
}

void Base64Tests::testShouldDecode() {
	CPPUNIT_ASSERT(base64::decode("SG9sYSBNdW5kbyE=") == "Hola Mundo!");
}

void Base64Tests::testShouldEncode() {

	std::string text = "Hola Mundo!";
	const unsigned char* buff = (const unsigned char *)text.c_str();
	CPPUNIT_ASSERT(base64::encode(buff, text.size()) == "SG9sYSBNdW5kbyE=");
}
