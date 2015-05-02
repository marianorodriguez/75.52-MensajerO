#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <curl/curl.h>
#include "services/RestServerTest.h"
#include "services/ServiceFactoryTest.h"
#include "logger/LoggerTest.h"
#include "rest-client/RestClientTest.h"
#include "ArgsParserTests.h"
#include "NumberConverterTests.h"

int main(int argc, char* argv[]){
	curl_global_init(CURL_GLOBAL_ALL);

	CPPUNIT_NS::TestResult controller;
	CPPUNIT_NS::TestResultCollector result;

	controller.addListener( &result );
	CPPUNIT_NS::BriefTestProgressListener progress;

	controller.addListener( &progress );
	CPPUNIT_NS::TestRunner runner;

	// Instancio para que ejecuten las pruebas
	//ArgsParserTests apt;
	LoggerTest lt;
	RestClientTest rct;
	RestServerTest rst;
	ServiceFactoryTest sft;
	NumberConverterTests nct;

	runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
	runner.run( controller );

	CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
	outputter.write();

	curl_global_cleanup();

	return result.wasSuccessful() ? 0 : 1;
}
