project(mensajero)

# Archivos del servidor
if(coverage-test)
	message(STATUS "Compilando soporte para coverage-tests")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif(coverage-test)

add_executable(server
	main.cpp
	services/ServerConfig.cpp
	)

# Archivos del modelo en general
add_library(mensajero-model
	exceptions/BaseException.cpp
	exceptions/FileNotFoundException.cpp
	exceptions/InvalidKeyException.cpp
	exceptions/InvalidUsernameException.cpp
	exceptions/KeyNotFoundException.cpp
	exceptions/NotSerializedDataException.cpp
	user/User.cpp
	user/chat/Chat.cpp
	user/chat/Message.cpp
	)

target_link_libraries(server ${JSONCPP_LIBRARIES} mensajero-database
					mensajero-services mensajero-model mensajero-utilities)

if(coverage-test)
	target_link_libraries(server gcov)
	target_link_libraries(mensajero-model gcov)
endif(coverage-test)

# Paths absolutos
include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(database)
add_subdirectory(services)
add_subdirectory(utilities)

