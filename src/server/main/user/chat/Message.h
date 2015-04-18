#ifndef SERVER_MAIN_USER_MESSAGE_H_
#define SERVER_MAIN_USER_MESSAGE_H_
#include "../../interfaces/Serializable/ISerializable.h"
#include "../../exceptions/NotSerializedDataException.h"
#include "../../exceptions/InvalidUsernameException.h"
#include "../../tests/user/chat/messageTests.h"
#include "../../utilities/Date.h"
#include "../../utilities/Time.h"
#include "json/json.h"
#include<iostream>
using namespace std;

/**
 * Esta clase define un único mensaje entre dos usuarios.
 */
class Message: public ISerializable {

	friend messageTests;

public:
	/**
	 * Permite construir un nuevo mensaje deserializando un string JSON.
	 * @params toDeserialize Contiene el mensaje serializado mediante JSON.
	 */
	Message(const string& toDeserialize);

	/**
	 * Permite construir un nuevo mensaje indicandole sus atributos.
	 * @params from El emisor del mensaje.
	 * @params to El receptor del mensaje.
	 * @params message El mensaje a enviar.
	 */
	Message(const string& from, const string& to, const string& message);
	virtual ~Message();

	/**
	 * Serializa una instancia de mensaje retornando el string JSON.
	 */
	string serialize() const override;

	/**
	 * Devuelve el texto del mensaje.
	 */
	string getText() const;

	/**
	 * Devuelve el destinatario del mensaje.
	 */
	string getUserTo() const;

	/**
	 * Devuelve el emisor del mensaje.
	 */
	string getUserFrom() const;

	/**
	 * Devuelve la fecha en que se creó el mensaje.
	 */
	string getDate() const;

	/**
	 * Devuelve la hora en la que se creó el mensaje.
	 */
	string getTime() const;

	bool getSent() const;
	void setAsSent();

private:
	bool sent;

	string userFromID;
	string userToID;
	string date;
	string time;
	string message;
};

#endif /* SERVER_MAIN_USER_MESSAGE_H_ */
