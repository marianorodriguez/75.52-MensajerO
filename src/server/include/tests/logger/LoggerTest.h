#ifndef SERVER_TESTS_LOGGER_LOGGERTESTS_H_
#define SERVER_TESTS_LOGGER_LOGGERTESTS_H_

#include <cppunit/extensions/HelperMacros.h>

class LoggerTest: public CPPUNIT_NS::TestFixture {

	CPPUNIT_TEST_SUITE(LoggerTest);

	CPPUNIT_TEST(should_be_singleton);
	CPPUNIT_TEST(should_instantiate_logger);
	CPPUNIT_TEST(should_return_log_path);
	CPPUNIT_TEST(should_write_only_an_error);
	CPPUNIT_TEST(should_write_only_a_warning);
	CPPUNIT_TEST(should_write_only_a_debug);
	CPPUNIT_TEST(should_write_only_an_info);
	CPPUNIT_TEST(should_return_loggingLevels);
	CPPUNIT_TEST(should_throw_file_not_found_exception);
	CPPUNIT_TEST(should_start_stop_logger);
	CPPUNIT_TEST_SUITE_END();

private:

protected:
	void should_be_singleton();
	void should_instantiate_logger();
	void should_return_log_path();
	void should_write_only_an_error();
	void should_write_only_a_warning();
	void should_write_only_a_debug();
	void should_write_only_an_info();
	void should_return_loggingLevels();
	void should_throw_file_not_found_exception();
	void should_be_thread_safe();
	void should_start_stop_logger();
};

#endif
