#ifndef CONFIG_CONFIG_H_
#define CONFIG_CONFIG_H_
#include "profPicture.h"

//# JSON ######################################
/**
 * Ruta al archivo de configuración de JSON.
 */
#define JSON_CONFIG_FILE "config/config.json"

//# ESTRUCTURA DE UN MENSAJE JSON
#define JSON_MSG_FROM_VALUE "msg_fromID"
#define JSON_MSG_TO_VALUE "msg_toID"
#define JSON_MSG_DATE_VALUE "msg_date"
#define JSON_MSG_TIME_VALUE "msg_time"
#define JSON_MSG_TEXT "msg_text"
#define JSON_MSG_SENT "sent"

//# ESTRUCTURA DE UN CHAT JSON
#define JSON_CHAT_USER_1 "username_1"
#define JSON_CHAT_USER_2 "username_2"
#define JSON_CHAT_MESSAGES "messages"

//# ESTRUCTURA DE UN USER JSON
#define JSON_USER_NAME "username"
#define JSON_USER_PWD "password"
#define JSON_USER_LOCATION "location"
#define JSON_USER_STATUS "status"
#define JSON_USER_PROFILE_PICTURE "profile_picture"
#define JSON_USER_CHATS_WITH "chats_with"

//# USER ######################################
#define DEFAULT_USER_LOCATION "UNKNOWN"
#define DEFAULT_USER_STATUS "Online"
#define DEFAULT_USER_PROFILE_PICTURE DEF_PROF_PICT


//# DATABASE ##################################
const std::string DEFAULT_DATABASE_PATH = "database";
#define DATABASE_CHATS_PATH "database/chats"
#define DATABASE_USERS_PATH "database/users"


//# LOGGER ####################################
/**
 * Ruta por defecto al archivo de logging.
 */
#define DEFAULT_LOGGING_FILE "logging.txt"

//# SERVICES ##################################

#define SERVICE_USERNAME "username"
#define SERVICE_PASSWORD "password"

//# SERVICIO DE SIGNUP
const std::string SERVICE_SIGNUP_NAME = "signUp";

//# SERVICIO DE LOGIN
const std::string SERVICE_LOGIN_NAME = "logIn";

//# SERVICIO DE SENDMESSAGE
const std::string SERVICE_SENDMESSAGE_NAME = "sendMessage";
#define SERVICE_SENDMESSAGE_USERNAME_TO "msg_toID"
#define SERVICE_SENDMESSAGE_MESSAGE "msg_text"

//# SERVICIO DE SOMETHINGFORME
const std::string SERVICE_SOMETHINGFORME_NAME = "somethingForMe";
const std::string SERVICE_SOMETHINGFORME_MESSAGES = "messages";

//# SERVICIO DE CURRENTCHATS
const std::string SERVICE_CURRENTCHATS_NAME = "currentChats";
const std::string SERVICE_CURRENTCHATS_CHATS = "chats";

//# SERVICIO DE UserConfig
const std::string SERVICE_USERCONFIG_NAME = "setConfig";
const std::string SERVICE_USERCONFIG_LOCATION = "location";
const std::string SERVICE_USERCONFIG_STATUS = "status";
const std::string SERVICE_USERCONFIG_PICTURE = "profile_picture";

//# SERVICIO DE USERS
const std::string SERVICE_USERS_NAME = "users";

//# OUTPUT DE LOS SERVICES
const std::string SERVICE_OUT_OK = "ok";
const std::string SERVICE_OUT_WHAT = "what";
const std::string SERVICE_OUT_INVALIDUSER = "Error: Invalid username.";
const std::string SERVICE_OUT_USERNAMEEXISTS = "Error: Username already exists.";
const std::string SERVICE_OUT_INVALIDPWD = "Error: Invalid password.";

#endif /* CONFIG_CONFIG_H_ */
