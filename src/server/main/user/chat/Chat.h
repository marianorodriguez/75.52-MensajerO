/*
 * Chat.h
 *
 *  Created on: 2/4/2015
 *      Author: marian
 */

#ifndef SERVER_MAIN_USER_CHAT_CHAT_H_
#define SERVER_MAIN_USER_CHAT_CHAT_H_

#include "../../../tests/user/chat/chatTests.h"
#include "interfaces/ISerializable.h"
#include "exceptions/InvalidUsernameException.h"
#include "Message.h"

class chatTests;

/**
 * Esta clase define un chat entre dos usuarios diferentes.
 */
class Chat: public ISerializable {
	friend chatTests;

public:

	/**
	 * Inicializa un chat existente pasandole por parametros una cadena de texto con los datos del chat.
	 */
	Chat(const string &serializedChat);

	/**
	 * Inicializa un nuevo chat pasandole como parametro los usuarios vinculados.
	 */
	Chat(const string& user1, const string& user2);
	virtual ~Chat();

	/**
	 * Agrega un nuevo mensaje al chat actual.
	 * @params msg Puntero al mensaje a agregar.
	 */
	void addNewMessage(Message* msg);

	/**
	 * Serializa el chat en una cadena de texto.
	 */
	string serialize() const override;

private:
	string username_1;
	string username_2;
	int numberOfMessages;
	vector<Message*> sentMessages;

	/**
	 * Chequea si el mensaje pasado por parametro puede ser un mensaje valido para el chat actual.
	 */
	bool isAValidMessage(const Message& m) const;
};

#endif /* SERVER_MAIN_USER_CHAT_CHAT_H_ */
