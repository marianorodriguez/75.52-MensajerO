#ifndef CPP_UNIT_EXAMPLETESTCASE_H
#define CPP_UNIT_EXAMPLETESTCASE_H

#include <cppunit/extensions/HelperMacros.h>

class loggerTests: public CPPUNIT_NS::TestFixture {

	CPPUNIT_TEST_SUITE( loggerTests );

	CPPUNIT_TEST(should_instantiate_logger);
	CPPUNIT_TEST(should_return_log_path);
	CPPUNIT_TEST(should_write_an_issue);
	CPPUNIT_TEST(should_stamp_time_and_date);
	CPPUNIT_TEST(should_return_loggingLevels);
	CPPUNIT_TEST(should_set_logging_levels);

	CPPUNIT_TEST_SUITE_END();

private:

protected:
	void should_instantiate_logger();
	void should_return_log_path();
	void should_write_an_issue();
	void should_stamp_time_and_date();
	void should_return_loggingLevels();
	void should_set_logging_levels();
};

#endif
