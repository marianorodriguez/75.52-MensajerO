project(mensajero)

#Archivos del servidor
add_executable(server
	main.cpp)

target_link_libraries(server ${ROCKSDB_LIBRARIES} ${JSONCPP_LIB} mongoose pthread z bz2)

