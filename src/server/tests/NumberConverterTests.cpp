#include <string>
#include "NumberConverterTests.h"
#include "utilities/NumberConverter.h"

CPPUNIT_TEST_SUITE_REGISTRATION(NumberConverterTests);

void NumberConverterTests::setUp(){
	CppUnit::TestFixture::setUp();
}

void NumberConverterTests::tearDown(){
	CppUnit::TestFixture::tearDown();
}

void NumberConverterTests::testValidNumbers(){
	std::string num1("123");
	std::string numFloat("1.54");
	CPPUNIT_ASSERT(NumberConverter::isNumber(num1));
	CPPUNIT_ASSERT(NumberConverter::isNumber(numFloat));
}

void NumberConverterTests::testInvalidNumbers(){
	std::string num1("hola");
	std::string num2("1!3");
	CPPUNIT_ASSERT(!NumberConverter::isNumber(num2));
	CPPUNIT_ASSERT(!NumberConverter::isNumber(num1));
}

void NumberConverterTests::testParseValidNumbers(){
	std::string num1("123");
	std::string num2("8");
	CPPUNIT_ASSERT_EQUAL(123, NumberConverter::getNumber(num1));
	CPPUNIT_ASSERT_EQUAL(8, NumberConverter::getNumber(num2));
}

