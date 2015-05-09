Servicios
=========

A continuación se muestra el formato de datos con el que se comunican los servicios Rest.


Log In Activity
---------------

Servicio: */logIn* (POST)

Cliente manda: ::

	{ 
	"logInService" : { 
		"username" : <username>,
		"password" : <md5_password>
		} 
	}

Servidor responde: ::

	{ 
	"user" : { 
		"location" : <user_location>, 
		"status" : <user_status>, 
		"profile_picture" : <base64_picture>, 
		"username" : <username>
		} 
	}

O mensaje de error en caso de falla.	

Sign Up Activity
----------------

Servicio: */signUp* (POST)

cliente manda: ::

	{ 
	"signUpService" : { 
		"username" : <username>,
		"password" : <md5_password>
		} 
	}

Servidor responde igual que en logIn.

Configuration Activity
----------------------

servicio: */setConfig* (POST)
cliente manda: ::

	{ 
	"user" : { 
		"location" : <new_location>, 
		"status" : <new_status>, 
		"profile_picture" : <new_base64_valid_picture>, 
		"username" : <username>
		"password" : <md5_password>
		} 
	}
	
Servidor responde igual que en logIn (con los datos actualizados).

Chats Activity
--------------

Servicio: */somethingForMe*  (GET)

Mensajes nuevos para este usuario

Cliente manda parametros: “username” y “password” (encriptada en md5)

Servidor responde: ::

	{ 
	"new_messages" : {
		"message" : [ <vector de Messages>  ],
		"numberOfMessages" :<int>
		}
	}

Estructura de un Message: ::

	{ 
	"message" : { 
		"msg_date" : "15/04/2015", 
		"msg_fromID" : <user emisor>, 
		"msg_text" : <mensaje>, 
		"msg_time" : "06:55", 
		"msg_toID" : <user receptor>
		} 
	}

Current chats
-------------

Servicio: */currentChats* (GET)

Cliente manda parametros: “username” y “password” (encriptada en md5)

Servidor responde: ::

	{ 
	"currentChats" : {
		"chatsWith" : [ <vector de Users> ],
		"numberOfChats" : <int>
		}
	}

estructura de un User: ::

	{
	"user" : { 
		"location" : <user_location>, 
		"status" : <user_status>, 
		"profile_picture" : <base64_picture>, 
		"username" : <username>
		} 
	}

Get users
---------

Servicio: */users* (GET)

cliente manda parametros: “username” y “password” (encriptada en md5)

Servidor responde: ::

	{ 
	"registeredUsers": {
		"users" : [ <vector de Users> ],
		"numberOfUsers" : <int>	
		}
	}

estructura de un User: ::

	{
	"user" : { 
		"location" : <user_location>, 
		"status" : <user_status>, 
		"profile_picture" : <base64_picture>, 
		"username" : <username>
		} 
	}

Chat Activity
-------------

Servicio: */sendMessage* (POST)

Cliente manda: ::

	{ 
	"sendMessageService" : { 
		"msg_fromID" : <user emisor>, 
		"msg_toID" : <user receptor>,
		"msg_text" : <mensaje>
		} 
	}

Servidor responde con un mensaje de *OK* o *ERROR*
