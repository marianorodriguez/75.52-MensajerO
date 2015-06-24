
#include "services/NullServiceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(NullServiceTest);

NullServiceTest::~NullServiceTest() {
}

void NullServiceTest::setUp() {
	ServiceTest::setUp();

	this->service = new NullService();
}

void NullServiceTest::tearDown() {
	ServiceTest::tearDown();
}

void NullServiceTest::testShouldGetUri(){
	CPPUNIT_ASSERT(this->service->getUri() == "");
}

void NullServiceTest::testdoNothing() {

	Json::Value input;
	input[SERVICE_USERNAME] = "username_1";
	input[SERVICE_PASSWORD] = "password";

	string output = service->executeRequest(input.toStyledString());

	CPPUNIT_ASSERT(output == "");
}
