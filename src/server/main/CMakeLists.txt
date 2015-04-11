project(mensajero)

#Archivos del servidor
add_executable(server
	main.cpp
	exceptions/BaseException.cpp
	exceptions/FileNotFoundException.cpp
	exceptions/InvalidKeyException.cpp
	exceptions/InvalidUsernameException.cpp
	exceptions/KeyNotFoundException.cpp
	exceptions/NotSerializedDataException.cpp
	logger/Logger.cpp)

target_link_libraries(server ${ROCKSDB_LIBRARIES} ${JSONCPP_LIBRARIES}
					mensajero-services mensajero-utilities pthread z bz2)


# Paths absolutos
include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(services)
add_subdirectory(utilities)
