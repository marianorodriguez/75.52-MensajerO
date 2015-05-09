#ifndef RESTSERVERTEST_H
#define RESTSERVERTEST_H

#include "cppunit/extensions/HelperMacros.h"
#include "services/RestServer.h"
#include "services/ServerThread.h"

/**
 * Tests sobre la colección de servicios
 */
class RestServerTest : public CppUnit::TestFixture{
	CPPUNIT_TEST_SUITE(RestServerTest);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST(testEchoReply);
	CPPUNIT_TEST_SUITE_END();

public:
    virtual ~RestServerTest();
	void setUp();
	void tearDown();
	/**
	 * Compruebo que el servidor se instancie correctamente
	 */
	void testConstructor();
	/**
	 * Compruebo que pueda responder a un request con un servicios
	 * de prueba EchoService.
	 */
	void testEchoReply();
private:
	ServerThread* testServer;
};

#endif // RESTSERVERTEST_H

