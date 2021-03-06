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
#include "../../include/tests/services/BroadcastServiceTest.h"
#include "../../include/tests/LocationManagerTests.h"
#include "../../include/tests/services/NullServiceTest.h"
#include "../../include/tests/services/ServerConfigTest.h"

int main(int argc, char* argv[]){
	curl_global_init(CURL_GLOBAL_ALL);

	CPPUNIT_NS::TestResult controller;
	CPPUNIT_NS::TestResultCollector result;

	controller.addListener( &result );
	CPPUNIT_NS::BriefTestProgressListener progress;

	controller.addListener( &progress );
	CPPUNIT_NS::TestRunner runner;

	// Instancio para que ejecuten las pruebas
	//*ArgsParserTests apt;
	ServerConfigTest sct;
	NullServiceTest nst;
	BroadcastServiceTest bst;
	CurrentChatsServiceTest ccst;
	DatabaseTests dbt;
	DeleteChatServiceTest dcst;
	LocationManagerTests lmt;
	LoggerTest lt;
	LogInServiceTest lst;
	NumberConverterTests nct;
	RestClientTest rct;
	RestServerTest rst;
	SendMessageServiceTest smst;
	ServiceFactoryTest sft;
	SignUpServiceTest sust;
	SomethingForMeServiceTest sfmst;
	UserConfigServiceTest ucst;
	UsersServiceTest ust;

	runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
	runner.run( controller );

	CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
	outputter.write();

	curl_global_cleanup();

	return result.wasSuccessful() ? 0 : 1;
}
