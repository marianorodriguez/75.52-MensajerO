#ifndef CONFIG_CONFIG_H_
#define CONFIG_CONFIG_H_

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

//# ESTRUCTURA DE UN CHAT JSON
#define JSON_CHAT_ROOT "chat"
#define JSON_CHAT_USER_1 "username_1"
#define JSON_CHAT_USER_2 "username_2"
#define JSON_CHAT_NUM_MSG "number_of_messages"
#define JSON_CHAT_MESSAGES "messages"

//# LOGGER ####################################
/**
 * Ruta por defecto al archivo de logging.
 */
#define DEFAULT_LOGGING_FILE "logging.txt"





#endif /* CONFIG_CONFIG_H_ */
