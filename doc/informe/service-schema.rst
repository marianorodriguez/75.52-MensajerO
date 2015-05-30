Servicios
=========

A continuación se muestra el formato de datos con el que se comunican los servicios Rest.


Log In Activity
---------------

Servicio: */logIn* (POST)

Cliente manda: ::

	{ 
		"username" : <username>,
		"password" : <md5_password>,
		"location” : <coordenadas>,
		"status" : <new_status>, 
		"profile_picture" : <new_base64_valid_picture>
	}

Servidor responde: ::

	{ 
		"ok" : true/false,
		“what” : invalid user/invalid password
	}

Sign Up Activity
----------------

Servicio: */signUp* (POST)

Cliente manda: ::

	{ 
		"username" : <username>,
		"password" : <md5_password>,
		“location” : <coordenadas>
	}

Servidor responde: ::

	{ 
		"ok" : true/false,
		“what” : “”/invalid user
	}

Configuration Activity
----------------------

Servicio: */setConfig* (POST)
Cliente manda: ::

	{ 
		"username" : <username>,
		"password" : <md5_password>,
		"location” : <coordenadas>,
		"status" : <new_status>, 
		"profile_picture" : <new_base64_valid_picture>
	}
	
Servidor responde: ::
	
	{ 
      	"ok" : true/false,
		“what” : “”/invalid user
	}

Chats Activity
--------------

Servicio: */somethingForMe*  (GET)

Mensajes nuevos para este usuario

Cliente manda: ::

	{
	      	"username" : <username>,
	     	"password" : <md5_password>,
		“location” : <coordenadas>
	}

Servidor responde: ::

	{ 
	"messages" : [ <vector de Messages>  ]
	}

Estructura de un Message: ::

	{ 
	"msg_date" : "dd/mm/aaaa", 
	"msg_fromID" : <user emisor>, 
	"msg_text" : <mensaje>, 
	"msg_time" : "hh:mm", 
	"msg_toID" : <user receptor>
	}

Current chats
-------------

Servicio: */currentChats* (GET)

Cliente manda: ::

	{ 
      	"username" : <username>,
     	"password" : <md5_password>,
	“location” : <coordenadas>
	}

Servidor responde: ::

	{ 
	"chats" : [ <vector de chats> ]
	}

Estructura de un Chat: ::

	{ 
	"username_1" : <username>,
	“username_2” : <username>,
	“messages” : [<vector de messages>] 
	}

Estructura de un User: ::

	{
	"location" : <user_location>, 
	"status" : <user_status>, 
	"profile_picture" : <base64_picture>, 
	"username" : <username>
	}

Estructura de un Message: ::

	{ 
	"msg_date" : "15/04/2015", 
	"msg_fromID" : <user emisor>, 
	"msg_text" : <mensaje>, 
	"msg_time" : "06:55", 
	"msg_toID" : <user receptor>
	}

Get users
---------

Servicio: */users* (GET)

Cliente manda: :: 

	{ 
      	"username" : <username>,
     	"password" : <md5_password>,
	“location”: <coordenadas>
	}

Servidor responde: ::

	{ 
	"users" : [ <vector de Users> ]
	}

Estructura de un User: ::

	{
        "location" : <user_location>, 
        "status" : <user_status>, 
        "profile_picture" : <base64_picture>, 
        "username" : <username>
	}

Chat Activity
-------------

Servicio: */sendMessage* (POST)

Cliente manda: ::

	{ 
        "username" : <username>,
        "password" : <md5_password>,
        "location" : <coordenadas>,
        "msg_toID" : <user receptor>,
        "msg_text" : <mensaje>
	}

Servidor responde: ::

	{ 
      	"ok" : true/false,
	“what” : invalid user
	}
