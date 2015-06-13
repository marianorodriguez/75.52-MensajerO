#ifndef SERVER_MAIN_USER_USER_H_
#define SERVER_MAIN_USER_USER_H_

#include "ISerializable.h"
#include "../exceptions/InvalidUsernameException.h"
#include "../exceptions/NotSerializedDataException.h"
#include <vector>
#include <iostream>
#include "../config.h"
using namespace std;

/**
 * Define a un usuario dentro del servidor.
 */
class User: public ISerializable {
	friend class userTests;

public:

	/**
	 * Inicializa un usuario pasandole por parametro sus atributos.
	 * @params username El username del usuario.
	 * @params pass La contraseña del usuario.
	 */
	User(const string& username, const string& pass);

	/**
	 * Inicializa un usuario pasandole como parametro una cadena de texto con su información previamente serializada.
	 */
	User(const string& serializedUser);
	virtual ~User();

	/**
	 * Serializa al usuario en una cadena de texto.
	 */
	string serialize() const override;

	/**
	 * Devuelve el username del usuario.
	 */
	string getUsername() const;

	/**
	 * Devuelve la contreseña del usuario.
	 */
	string getPassword() const;

	/**
	 * Devuelve la ubicación actual del usuario.
	 */
	string getLocation() const;

	/**
	 * Devuelve el estado del usuario.
	 */
	string getStatus() const;

	/**
	 * Devuelve la foto de perfil encriptada en base64.
	 */
	string getProfilePicture() const;

	/**
	 * Devuelve los usuarios con los que tiene chats.
	 */
	vector<string> getChats() const;

	/**
	 * Cambia la ubicación del usuario por la que es pasada como parametro.
	 * @params newLocation La nueva ubicación del usuario.
	 */
	void modifyLocation(const string& newLocation);

	/**
	 * Cambia el estado del usuario por el que es pasado como parametro.
	 * @params newStatus El nuevo estado del usuario.
	 */
	void modifyStatus(const string& newStatus);

	/**
	 * Modifica la foto de perfil por la que es pasada como parametro.
	 * @params newProfilePicture La nueva foto de perfil, previamente encriptada con base64.
	 */
	void modifyProfilePicture(const string& newProfilePicture);

	/**
	 * Agrega a la lista de chats propios el username del usuario con el que comienza un chat.
	 * @params user El username del usuario con el que comienza un chat.
	 */
	void addChatWithUser(const string& user);

	int getLastTimeConnected();
	void setLastTimeConnected();

	void setConnected(const bool &connected);
	bool isConnected() const;

private:

	int lastTimeConnected;

	string username;
	string password;

	string location;
	string status;
	string hashedProfilePicture;
	vector<string> hasChatsWith;
	bool connected;

	/**
	 * Se fija si el usuario tiene un chat con el usuario pasado por parametro.
	 * @params username El usuario con el que quiere ver si tiene un chat.
	 */
	bool isChattingWith(const string& username) const;
};

#endif /* SERVER_MAIN_USER_USER_H_ */
