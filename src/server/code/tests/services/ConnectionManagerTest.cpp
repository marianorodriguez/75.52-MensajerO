/*
 * ConnectionManagerTest.cpp
 *
 *  Created on: 27/4/2015
 *      Author: marian
 */

#include "services/ConnectionManagerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ConnectionManagerTest);


ConnectionManagerTest::~ConnectionManagerTest() {}

// TODO: Como no se puede instanciar testDb en el constructor, ver si
// se puede mejorar este setup
void ConnectionManagerTest::setUp(){
	TestFixture::setUp();
	testDb = new Database(DATABASE_USERS_PATH);
	manager.startUpdating();
}

void ConnectionManagerTest::tearDown(){
	TestFixture::tearDown();
	manager.stopUpdating();
	delete testDb;
}

void ConnectionManagerTest::testAddRecentlyConnectedUser() {

	std::string newUser = "Mariano";

	//verifico que el user no exista en la lista del manager
	it = manager.connectedUsers.find(newUser);
	CPPUNIT_ASSERT(it == manager.connectedUsers.end());

	manager.updateUser(*testDb, newUser);

	//verifico que el user se haya agregado a la lista
	it = manager.connectedUsers.find(newUser);
	CPPUNIT_ASSERT(it != manager.connectedUsers.end());
}

void ConnectionManagerTest::testUpdateAlreadyConnectedUser() {

	std::string newUser = "Mariano";
	manager.updateUser(*testDb, newUser);
	int userTime_1 = manager.connectedUsers[newUser];

	sleep(MAXIMUM_IDLE_TIME - 1); //dejo que pase 1 segundo para que se actualice el manager

	manager.updateUser(*testDb, newUser);
	int userTime_2 = manager.connectedUsers[newUser];

	CPPUNIT_ASSERT(userTime_1 < userTime_2);
}

void ConnectionManagerTest::testDisconnectUser() {

	std::string newUser = "Mariano";
	manager.updateUser(*testDb, newUser);

	//supero el timeOut para que el manager desconecte al usuario
	sleep(MAXIMUM_IDLE_TIME + 1);

	it = manager.connectedUsers.find(newUser);
	CPPUNIT_ASSERT(it == manager.connectedUsers.end());
}

void ConnectionManagerTest::testManageMultipleUsers() {

	std::vector<std::string> connectedUsers;
	std::string user_1 = "Mariano";
	std::string user_2 = "Matias";
	std::string user_3 = "Francisco";
	std::string user_4 = "Fernando";

	//agrego a todos los usuarios
	manager.updateUser(*testDb, user_1);
	manager.updateUser(*testDb, user_2);
	manager.updateUser(*testDb, user_3);
	manager.updateUser(*testDb, user_4);

	//se desconecta el user_1 (actualizo a todos menos a el)
	for (int i = 0; i <= MAXIMUM_IDLE_TIME + 1; i++) {
		sleep(1);
		manager.updateUser(*testDb, user_2);
		manager.updateUser(*testDb, user_3);
		manager.updateUser(*testDb, user_4);
	}

	//tienen que estar conectados los user 2, 3 y 4
	it = manager.connectedUsers.find(user_1);
	CPPUNIT_ASSERT(it == manager.connectedUsers.end());

	it = manager.connectedUsers.find(user_2);
	CPPUNIT_ASSERT(it != manager.connectedUsers.end());

	it = manager.connectedUsers.find(user_3);
	CPPUNIT_ASSERT(it != manager.connectedUsers.end());

	it = manager.connectedUsers.find(user_4);
	CPPUNIT_ASSERT(it != manager.connectedUsers.end());

	//se desconecta el user_4 (actualizo a todos menos a el)

	for (int i = 0; i <= MAXIMUM_IDLE_TIME + 1; i++) {
		sleep(1);
		manager.updateUser(*testDb, user_2);
		manager.updateUser(*testDb, user_3);
	}

	//tienen que estar conectados los user 2 y 3
	it = manager.connectedUsers.find(user_1);
	CPPUNIT_ASSERT(it == manager.connectedUsers.end());

	it = manager.connectedUsers.find(user_2);
	CPPUNIT_ASSERT(it != manager.connectedUsers.end());

	it = manager.connectedUsers.find(user_3);
	CPPUNIT_ASSERT(it != manager.connectedUsers.end());

	it = manager.connectedUsers.find(user_4);
	CPPUNIT_ASSERT(it == manager.connectedUsers.end());

	sleep(MAXIMUM_IDLE_TIME + 1);

	//todos desconectados
	it = manager.connectedUsers.find(user_1);
	CPPUNIT_ASSERT(it == manager.connectedUsers.end());

	it = manager.connectedUsers.find(user_2);
	CPPUNIT_ASSERT(it == manager.connectedUsers.end());

	it = manager.connectedUsers.find(user_3);
	CPPUNIT_ASSERT(it == manager.connectedUsers.end());

	it = manager.connectedUsers.find(user_4);
	CPPUNIT_ASSERT(it == manager.connectedUsers.end());
}

void ConnectionManagerTest::testGetConnectedUsers(){

	manager.updateUser(*testDb, "Mariano");
	manager.updateUser(*testDb, "Fernando");
	manager.updateUser(*testDb, "Zidane");

	std::vector<std::string> connectedUsers;

	connectedUsers = manager.getConnectedUsers();

	CPPUNIT_ASSERT(connectedUsers.at(0) == "Fernando");
	CPPUNIT_ASSERT(connectedUsers.at(1) == "Mariano");
	CPPUNIT_ASSERT(connectedUsers.at(2) == "Zidane");

	for (int i = 0; i <= MAXIMUM_IDLE_TIME + 1; i++) {
		sleep(1);
		manager.updateUser(*testDb, "Fernando");
		manager.updateUser(*testDb, "Zidane");
	}

	connectedUsers = manager.getConnectedUsers();
	CPPUNIT_ASSERT(connectedUsers.at(0) == "Fernando");
	CPPUNIT_ASSERT(connectedUsers.at(1) == "Zidane");
}
