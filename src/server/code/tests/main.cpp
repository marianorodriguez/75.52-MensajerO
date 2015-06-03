#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <curl/curl.h>
#include "../../include/tests/services/RestServerTest.h"
#include "../../include/tests/services/ServiceFactoryTest.h"
#include "../../include/tests/logger/LoggerTest.h"
#include "../../include/tests/rest-client/RestClientTest.h"
#include "../../include/tests/ArgsParserTests.h"
#include "../../include/tests/NumberConverterTests.h"
#include "../../include/tests/database/DatabaseTests.h"
#include "../../include/tests/services/LogInServiceTest.h"
#include "../../include/tests/services/SignUpServiceTest.h"
#include "../../include/tests/services/UserConfigServiceTest.h"
#include "../../include/tests/services/SomethingForMeServiceTest.h"
#include "../../include/tests/services/CurrentChatsServiceTest.h"
#include "../../include/tests/services/UsersServiceTest.h"
#include "../../include/tests/services/SendMessageServiceTest.h"
#include "../../include/tests/services/DeleteChatServiceTest.h"
#include "../../include/tests/LocationManagerTests.h"

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
	DatabaseTests dbt;
	RestClientTest rct;
	RestServerTest rst;
	ServiceFactoryTest sft;
	NumberConverterTests nct;
	LogInServiceTest lst;
	SignUpServiceTest sust;
	UserConfigServiceTest ucst;
	SomethingForMeServiceTest sfmst;
	CurrentChatsServiceTest ccst;
	UsersServiceTest ust;
	SendMessageServiceTest smst;
	DeleteChatServiceTest dcst;
	LocationManagerTests lmt;

	runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
	runner.run( controller );

	CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
	outputter.write();

	curl_global_cleanup();

	return result.wasSuccessful() ? 0 : 1;
}
