#ifndef SERVER_MAIN_USER_USER_H_
#define SERVER_MAIN_USER_USER_H_

#include "../interfaces/Serializable/ISerializable.h"
#include "../exceptions/InvalidUsernameException.h"
#include "../exceptions/NotSerializedDataException.h"
#include "../../tests/user/userTests.h"
#include "../utilities/MD5.h"
#include <vector>
#include <iostream>
using namespace std;

class userTests;
/**
 * Define a un usuario dentro del servidor.
 */
class User: public ISerializable{
	friend userTests;

public:

	/**
	 * Inicializa un usuario pasandole por parametro sus atributos.
	 * @params username El username del usuario.
	 * @params pass La contraseña del usuario.
	 */
	User(string username, string pass);

	/**
	 * Inicializa un usuario pasandole como parametro una cadena de texto con su información previamente serializada.
	 */
	User(string serializedUser);
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
	 * Devuelve la contreseña encriptada del usuario.
	 */
	string getHashedPWD() const;

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
	string getHashedProfilePicture() const;

	/**
	 * Cambia la ubicación del usuario por la que es pasada como parametro.
	 * @params newLocation La nueva ubicación del usuario.
	 */
	void modifyLocation(string newLocation);

	/**
	 * Cambia el estado del usuario por el que es pasado como parametro.
	 * @params newStatus El nuevo estado del usuario.
	 */
	void modifyStatus(string newStatus);

	/**
	 * Modifica la foto de perfil por la que es pasada como parametro.
	 * @params newProfilePicture La nueva foto de perfil, previamente encriptada con base64.
	 */
	void modifyProfilePicture(string newProfilePicture);

	/**
	 * Agrega a la lista de chats propios el username del usuario con el que comienza un chat.
	 * @params user El username del usuario con el que comienza un chat.
	 */
	void addChatWithUser(string user);

private:
	string username;
	string hashedPWD;
	string location;
	string status;
	string hashedProfilePicture;
	int numberOfChats;
	vector<string> hasChatsWith;

	/**Encripta la contreseña pasada por parametro */
	string encryptPassword(const string& plainPWD) const;

	/**
	 * Se fija si el usuario tiene un chat con el usuario pasado por parametro.
	 * @params username El usuario con el que quiere ver si tiene un chat.
	 */
	bool isChattingWith(const string& username);
};

#endif /* SERVER_MAIN_USER_USER_H_ */
