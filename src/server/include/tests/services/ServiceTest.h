/*
 * ServiceTest.h
 *
 *  Created on: 23/6/2015
 *      Author: marian
 */

#ifndef CODE_TESTS_SERVICES_SERVICETEST_H_
#define CODE_TESTS_SERVICES_SERVICETEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include "../../../include/main/config.h"
#include "../../../include/main/database/Database.h"
#include "../../../include/main/services/ServiceInterface.h"


class ServiceTest: public CppUnit::TestFixture {
public:
	virtual ~ServiceTest();

	void setUp();
	void tearDown();

protected:
	Database* userDB;
	Database* chatDB;
	ServiceInterface* service;

};

#endif /* CODE_TESTS_SERVICES_SERVICETEST_H_ */
