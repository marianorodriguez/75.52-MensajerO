#ifndef SERVER_TESTS_SERVICES_SIGNUPSERVICETEST_H_
#define SERVER_TESTS_SERVICES_SIGNUPSERVICETEST_H_

#include <services/SignUpService.h>
#include "cppunit/extensions/HelperMacros.h"


class SignUpServiceTest: public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(SignUpServiceTest);

	CPPUNIT_TEST(should_create_new_user);
	CPPUNIT_TEST(user_should_already_exist);

	CPPUNIT_TEST_SUITE_END();

public:
	void should_create_new_user();
	void user_should_already_exist();
};

#endif /* SERVER_TESTS_SERVICES_SIGNUPSERVICETEST_H_ */
