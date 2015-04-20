project(mensajero)

# Archivos del servidor
add_executable(server
	main.cpp
	database/Database.cpp
	utilities/Logger.cpp)

# Archivos del modelo en general
add_library(mensajero-model
	exceptions/BaseException.cpp
	exceptions/FileNotFoundException.cpp
	exceptions/InvalidKeyException.cpp
	exceptions/InvalidUsernameException.cpp
	exceptions/KeyNotFoundException.cpp
	exceptions/NotSerializedDataException.cpp
	interfaces/ISerializable.cpp
	user/User.cpp
	user/chat/Chat.cpp
	user/chat/Message.cpp
	)

target_link_libraries(server ${JSONCPP_LIBRARIES} mensajero-database
					mensajero-services mensajero-model mensajero-utilities)


# Paths absolutos
include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(database)
add_subdirectory(services)
add_subdirectory(utilities)
