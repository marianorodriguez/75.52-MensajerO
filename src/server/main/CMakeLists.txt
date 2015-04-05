project(mensajero)

#Archivos del servidor
add_executable(server
	main.cpp
	logger/logger.cpp)

target_link_libraries(server ${ROCKSDB_LIBRARIES} ${JSONCPP_LIBRARIES} services pthread z bz2)

add_subdirectory(services)