#include "../../include/tests/ArgsParserTests.h"
#include "../../include/main/ServerOptions.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ArgsParserTests);

void ArgsParserTests::setUp(){
	CppUnit::TestFixture::setUp();
}

void ArgsParserTests::tearDown(){
	CppUnit::TestFixture::tearDown();
}

void ArgsParserTests::testEmptyArgs(){
	// Argumentos a main() cuando llamo la aplicación sin argumentos
	int argc = 1;
	const char* argv[] = {"test"};
	OptionMap map = ArgsParser::parseArgs(argc, argv);
	CPPUNIT_ASSERT_MESSAGE("El mapa deberia ser vacio", map.size() == 0);
}

void ArgsParserTests::testValidArgs(){
	int argc = 4;
	const char* argv[] = {"test", "-p", "8080", "-ddb/path"};
	OptionMap map = ArgsParser::parseArgs(argc, argv);
	OptionMap::const_iterator it = map.find(ArgsParser::kServerPortKey);
	CPPUNIT_ASSERT_MESSAGE("No se encontro la opcion de puerto",
							it != map.end());
	CPPUNIT_ASSERT_MESSAGE("Puerto parseado incorrectamente",
							it->second.compare("8080") == 0);
	it = map.find(ArgsParser::kDatabaseKey);
	CPPUNIT_ASSERT_MESSAGE("No se encontro la opcion de database",
							it != map.end());
	CPPUNIT_ASSERT_MESSAGE("Database path parseado incorrectamente",
							it->second.compare("db/path") == 0);
}

void ArgsParserTests::testLongValidArgs(){
	int argc = 4;
	const char* argv[] = {"test", "-p", "8080", "--database=db/path"};
	OptionMap map = ArgsParser::parseArgs(argc, argv);
	OptionMap::const_iterator it = map.find(ArgsParser::kServerPortKey);
	CPPUNIT_ASSERT_MESSAGE("No se encontro la opcion larga de puerto",
							it != map.end());
	CPPUNIT_ASSERT_MESSAGE("Puerto parseado incorrectamente",
							it->second.compare("8080") == 0);
	it = map.find(ArgsParser::kDatabaseKey);
	CPPUNIT_ASSERT_MESSAGE("No se encontro la opcion larga de database",
							it != map.end());
	CPPUNIT_ASSERT_MESSAGE("Database path parseado incorrectamente",
							it->second.compare("db/path") == 0);
}

void ArgsParserTests::testInvalidArgs(){
	int argc = 4;
	const char* argv[] = {"test", "-x", "--config", "config/path", "-a"};
	OptionMap map = ArgsParser::parseArgs(argc, argv);
	CPPUNIT_ASSERT_MESSAGE("No se parsearon los argumentos correctamente",
							map.size() == 1);
	//OptionMap::const_iterator it = map.find(ArgsParser::kConfigKey);
	OptionMap::const_iterator it = map.find(ArgsParser::kConfigKey);
	CPPUNIT_ASSERT_MESSAGE("No se encontro la opcion de config",
							it != map.end());
	CPPUNIT_ASSERT_MESSAGE("Config parseado incorrectamente",
							it->second.compare("config/path") == 0);
}
