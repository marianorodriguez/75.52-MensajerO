#ifndef SERVER_MAIN_USER_MESSAGE_H_
#define SERVER_MAIN_USER_MESSAGE_H_
#include "../../interfaces/Serializable/ISerializable.h"
#include "../../exceptions/NotSerializedDataException.h"
#include "../../tests/user/chat/messageTests.h"
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
	Message(string toDeserialize);

	/**
	 * Permite construir un nuevo mensaje indicandole sus atributos.
	 * @params from El emisor del mensaje.
	 * @params to El receptor del mensaje.
	 * @params message El mensaje a enviar.
	 */
	Message(string date_time, string from, string to, string message);
	virtual ~Message();

	/**
	 * Serializa una instancia de mensaje retornando el string JSON.
	 */
	string serialize() override;

private:
	string userFromID;
	string userToID;
	string date_time;
	string message;
};

#endif /* SERVER_MAIN_USER_MESSAGE_H_ */
