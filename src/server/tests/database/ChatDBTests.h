/*
 * ChatDBTests.h
 *
 *  Created on: Apr 3, 2015
 *      Author: fran
 */

#ifndef CHATDBTESTS_H_
#define CHATDBTESTS_H_

#include <cppunit/extensions/HelperMacros.h>

class ChatDBTests: public CPPUNIT_NS::TestFixture  {
	CPPUNIT_TEST_SUITE(ChatDBTests);

	CPPUNIT_TEST(should_read_same_users);

	CPPUNIT_TEST_SUITE_END();

private:

protected:
	void should_read_same_users();
};

#endif /* CHATDBTESTS_H_ */
