#ifndef CONFIG_CONFIG_H_
#define CONFIG_CONFIG_H_
#include "profPicture.h"

//# JSON ######################################
/**
 * Ruta al archivo de configuración de JSON.
 */
#define JSON_CONFIG_FILE "config/config.json"

//# ESTRUCTURA DE UN MENSAJE JSON
#define JSON_MSG_ROOT "message"
#define JSON_MSG_FROM_VALUE "msg_fromID"
#define JSON_MSG_TO_VALUE "msg_toID"
#define JSON_MSG_DATE_VALUE "msg_date"
#define JSON_MSG_TIME_VALUE "msg_time"
#define JSON_MSG_TEXT "msg_text"
#define JSON_MSG_SENT "sent"

//# ESTRUCTURA DE UN CHAT JSON
#define JSON_CHAT_ROOT "chat"
#define JSON_CHAT_USER_1 "username_1"
#define JSON_CHAT_USER_2 "username_2"
#define JSON_CHAT_NUM_MSG "number_of_messages"
#define JSON_CHAT_MESSAGES "messages"

//# ESTRUCTURA DE UN USER JSON
#define JSON_USER_ROOT "user"
#define JSON_USER_NAME "username"
#define JSON_USER_PWD "password"
#define JSON_USER_LOCATION "location"
#define JSON_USER_STATUS "status"
#define JSON_USER_PROFILE_PICTURE "profile_picture"
#define JSON_USER_NUM_CHAT "number_of_chats"
#define JSON_USER_CHATS_WITH "chats_with"

//# USER ######################################
#define DEFAULT_USER_LOCATION "UNKNOWN"
#define DEFAULT_USER_STATUS "Online"
#define DEFAULT_USER_PROFILE_PICTURE DEF_PROF_PICT


//# DATABASE ##################################
#define DEFAULT_DATABASE_PATH "database"
#define DATABASE_CHAT_PATH "database/chat"


//# LOGGER ####################################
/**
 * Ruta por defecto al archivo de logging.
 */
#define DEFAULT_LOGGING_FILE "logging.txt"

//# SERVICES ##################################

//# SERVICIO DE SIGNUP
const std::string SERVICE_SIGNUP_NAME = "signUp";
#define SERVICE_SIGNUP_USERNAME "username"
#define SERVICE_SIGNUP_PASSWORD "password"

#endif /* CONFIG_CONFIG_H_ */
