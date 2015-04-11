project(mensajero)

#Archivos del servidor
add_executable(server
	main.cpp
	utilities/Base64.cpp
	utilities/Time.cpp
	utilities/Date.cpp
	utilities/MD5.cpp
	exceptions/BaseException.cpp
	exceptions/FileNotFoundException.cpp
	exceptions/InvalidKeyException.cpp
	exceptions/InvalidUsernameException.cpp
	exceptions/KeyNotFoundException.cpp
	exceptions/NotSerializedDataException.cpp
	logger/Logger.cpp)

target_link_libraries(server ${ROCKSDB_LIBRARIES} ${JSONCPP_LIBRARIES} services pthread z bz2)

# Paths absolutos
include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(services)
