/*
 * ConnectionManagerTest.cpp
 *
 *  Created on: 27/4/2015
 *      Author: marian
 */

#include <services/ConnectionManagerTest.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ConnectionManagerTest);

void ConnectionManagerTest::setUp() {

	this->manager = new ConnectionManager();
}

void ConnectionManagerTest::tearDown() {

	delete this->manager;
}

void ConnectionManagerTest::testAddRecentlyConnectedUser() {

	std::string newUser = "Mariano";

	//verifico que el user no exista en la lista del manager
	it = this->manager->connectedUsers.find(newUser);
	CPPUNIT_ASSERT(it == this->manager->connectedUsers.end());

	this->manager->updateUser(newUser);

	//verifico que el user se haya agregado a la lista
	it = this->manager->connectedUsers.find(newUser);
	CPPUNIT_ASSERT(it != this->manager->connectedUsers.end());
}

void ConnectionManagerTest::testUpdateAlreadyConnectedUser() {

	std::string newUser = "Mariano";
	this->manager->updateUser(newUser);

	int userTime_1 = this->manager->connectedUsers[newUser];

	sleep(1); //dejo que pase 1 segundo para modificar lasTimeConnected

	//actualizo el user
	this->manager->updateConnection();

	int userTime_2 = this->manager->connectedUsers[newUser];

	CPPUNIT_ASSERT(userTime_1 < userTime_2);
}

void ConnectionManagerTest::testDisconnectUser() {

	std::string newUser = "Mariano";
	this->manager->updateUser(newUser);

	sleep(this->manager->deltaTime +1); //supero el timeOut para desconectar a un usuario

	this->manager->updateConnection();

	it = this->manager->connectedUsers.find(newUser);
	CPPUNIT_ASSERT(it == this->manager->connectedUsers.end());
}

void ConnectionManagerTest::testManageMultipleUsers(){

	std::string user_1 = "Mariano";
	std::string user_2 = "Matias";
	std::string user_3 = "Francisco";
	std::string user_4 = "Fernando";

	//agrego a todos los usuarios
	this->manager->updateUser(user_1);
	this->manager->updateUser(user_2);
	this->manager->updateUser(user_3);
	this->manager->updateUser(user_4);

	//se desconecta el user_1 (actualizo a todos menos a el)

	for(int i=0; i <= this->manager->deltaTime +1; i++){
		sleep(1);
		this->manager->updateUser(user_2);
		this->manager->updateUser(user_3);
		this->manager->updateUser(user_4);
	}

	this->manager->updateConnection();

	//tienen que estar conectados los user 2, 3 y 4

	it = this->manager->connectedUsers.find(user_1);
	CPPUNIT_ASSERT(it == this->manager->connectedUsers.end());

	it = this->manager->connectedUsers.find(user_2);
	CPPUNIT_ASSERT(it != this->manager->connectedUsers.end());

	it = this->manager->connectedUsers.find(user_3);
	CPPUNIT_ASSERT(it != this->manager->connectedUsers.end());

	it = this->manager->connectedUsers.find(user_4);
	CPPUNIT_ASSERT(it != this->manager->connectedUsers.end());

	//se desconecta el user_4 (actualizo a todos menos a el)

	for(int i=0; i <= this->manager->deltaTime +1; i++){
		sleep(1);
		this->manager->updateUser(user_2);
		this->manager->updateUser(user_3);
	}

	this->manager->updateConnection();

	//tienen que estar conectados los user 2 y 3
	it = this->manager->connectedUsers.find(user_1);
	CPPUNIT_ASSERT(it == this->manager->connectedUsers.end());

	it = this->manager->connectedUsers.find(user_2);
	CPPUNIT_ASSERT(it != this->manager->connectedUsers.end());

	it = this->manager->connectedUsers.find(user_3);
	CPPUNIT_ASSERT(it != this->manager->connectedUsers.end());

	it = this->manager->connectedUsers.find(user_4);
	CPPUNIT_ASSERT(it == this->manager->connectedUsers.end());

	sleep(manager->deltaTime +1);

	this->manager->updateConnection();

	//todos desconectados
	it = this->manager->connectedUsers.find(user_1);
	CPPUNIT_ASSERT(it == this->manager->connectedUsers.end());

	it = this->manager->connectedUsers.find(user_2);
	CPPUNIT_ASSERT(it == this->manager->connectedUsers.end());

	it = this->manager->connectedUsers.find(user_3);
	CPPUNIT_ASSERT(it == this->manager->connectedUsers.end());

	it = this->manager->connectedUsers.find(user_4);
	CPPUNIT_ASSERT(it == this->manager->connectedUsers.end());
}
