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
#include "../utilities/Mutex.h"
#include "../database/Database.h"

/**
 * Encargada de detectar usuarios que se conectan y desconectan al servidor.
 */
class ConnectionManager{
	friend class ConnectionManagerTest;

public:

	static ConnectionManager* getInstance();
	static void destroyInstance();
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

	/**
	 * TODO: Que la BD se setee en el constructor (implica que esta clase no sea
	 * singleton)
	 */
	void setDatabase(Database* userDb);
	/**
	 * Indica el tiempo en segundos que un usuario permanece "conectado"
	 */
	void setUserAliveTime(int deltaTime);
private:

	ConnectionManager();
	static ConnectionManager* managerInstance;
	static Mutex constructorMutex;

	/**
	 * Recorre la lista de usuarios conectados, se fija cuando fue la ultima
	 * vez que le llegó algo, y lo elimina de esa lista en caso de detectar
	 * que se desconectó.
	 */
	void updateConnection();

	/**
	 * Función que ejecuta el thread para automatizar las actualizaciones.
	 */
	static void* runFunction(void* args);
	/**
	 * Base de datos de usuarios
	 * TODO: que sea una referencia
	 */
	Database* userDb;
	Mutex mtx;
	pthread_t updateThread;
	std::map<std::string, int> connectedUsers;
	std::map<std::string, int>::iterator it;
	bool running;
	// Tiempo en el que un usuario se desconecta
	int deltaTime;
	static const int kDefaultDeltaTime;
};

#endif /* SERVER_MAIN_SERVICES_CONNECTIONMANAGER_H_ */
