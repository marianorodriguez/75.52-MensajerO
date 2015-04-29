/*
 * ConnectionManager.h
 *
 *  Created on: 27/4/2015
 *      Author: marian
 */

#ifndef SERVER_MAIN_SERVICES_CONNECTIONMANAGER_H_
#define SERVER_MAIN_SERVICES_CONNECTIONMANAGER_H_

#include <map>
#include <vector>
#include <thread>
#include <unistd.h>
#include "utilities/Mutex.h"

class ConnectionManager{
	friend class ConnectionManagerTest;

public:

	static ConnectionManager* getInstance();
	virtual ~ConnectionManager();

	/**
	 * Inicia el thread para actualizar las conexiones cada cierto tiempo.
	 */
	void startUpdating();

	/**
	 * Devuelve una lista de los usuarios actualmente conectados, ordenada alfabeticamente.
	 */
	std::vector<std::string> getConnectedUsers();

	/**
	 * Actualiza el estado del usuario pasado en @param username.
	 */
	void updateUser(const std::string username);

	/**
	 * Detiene y destruye el thread para actualizar las conexiones.
	 */
	void stopUpdating();

private:

	ConnectionManager();
	static ConnectionManager* managerInstance;

	/**
	 * Recorre la lista de usuarios conectados, se fija cuando fue la ultima
	 * vez que le llegó algo, y lo elimina de esa lista en caso de detectar
	 * que se desconectó.
	 */
	static void updateConnection();

	/**
	 * Función que ejecuta el thread para automatizar las actualizaciones.
	 */
	static void* runFunction(void* args);

	static Mutex mtx;
	static Mutex constructorMutex;
	pthread_t updateThread;
	static std::map<std::string, int> connectedUsers;
	std::map<std::string, int>::iterator it;
	static int deltaTime;
	static bool running;
};

#endif /* SERVER_MAIN_SERVICES_CONNECTIONMANAGER_H_ */
