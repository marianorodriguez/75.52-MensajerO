/*
 * ConnectionManagerTest.cpp
 *
 *  Created on: 27/4/2015
 *      Author: marian
 */

#include "services/ConnectionManagerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ConnectionManagerTest);

ConnectionManagerTest::ConnectionManagerTest() {}

ConnectionManagerTest::~ConnectionManagerTest() {}

void ConnectionManagerTest::setUp(){
	TestFixture::setUp();
	manager.startUpdating();
}

void ConnectionManagerTest::tearDown(){
	TestFixture::tearDown();
	manager.stopUpdating();
}

void ConnectionManagerTest::testAddRecentlyConnectedUser() {

	std::string newUser = "Mariano";

	//verifico que el user no exista en la lista del manager
	it = manager.connectedUsers.find(newUser);
	CPPUNIT_ASSERT(it == manager.connectedUsers.end());

	manager.updateUser(newUser);

	//verifico que el user se haya agregado a la lista
	it = manager.connectedUsers.find(newUser);
	CPPUNIT_ASSERT(it != manager.connectedUsers.end());
}

void ConnectionManagerTest::testUpdateAlreadyConnectedUser() {

	std::string newUser = "Mariano";
	manager.updateUser(newUser);
	int userTime_1 = manager.connectedUsers[newUser];

	sleep(manager.deltaTime-1); //dejo que pase 1 segundo para que se actualice el manager

	manager.updateUser(newUser);
	int userTime_2 = manager.connectedUsers[newUser];

	CPPUNIT_ASSERT(userTime_1 < userTime_2);
}

void ConnectionManagerTest::testDisconnectUser() {

	std::string newUser = "Mariano";
	manager.updateUser(newUser);

	//supero el timeOut para que el manager desconecte al usuario
	sleep(manager.deltaTime + 1);

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
	manager.updateUser(user_1);
	manager.updateUser(user_2);
	manager.updateUser(user_3);
	manager.updateUser(user_4);

	//se desconecta el user_1 (actualizo a todos menos a el)
	for (int i = 0; i <= manager.deltaTime + 1; i++) {
		sleep(1);
		manager.updateUser(user_2);
		manager.updateUser(user_3);
		manager.updateUser(user_4);
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

	for (int i = 0; i <= manager.deltaTime + 1; i++) {
		sleep(1);
		manager.updateUser(user_2);
		manager.updateUser(user_3);
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

	sleep(manager.deltaTime + 1);

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

	manager.updateUser("Mariano");
	manager.updateUser("Fernando");
	manager.updateUser("Zidane");

	std::vector<std::string> connectedUsers;

	connectedUsers = manager.getConnectedUsers();

	CPPUNIT_ASSERT(connectedUsers.at(0) == "Fernando");
	CPPUNIT_ASSERT(connectedUsers.at(1) == "Mariano");
	CPPUNIT_ASSERT(connectedUsers.at(2) == "Zidane");

	for (int i = 0; i <= manager.deltaTime + 1; i++) {
		sleep(1);
		manager.updateUser("Fernando");
		manager.updateUser("Zidane");
	}

	connectedUsers = manager.getConnectedUsers();
	CPPUNIT_ASSERT(connectedUsers.at(0) == "Fernando");
	CPPUNIT_ASSERT(connectedUsers.at(1) == "Zidane");
}