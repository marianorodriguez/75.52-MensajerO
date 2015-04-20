project(mensajero)

include_directories(${PROJECT_SOURCE_DIR}/../main)

add_subdirectory(rest-client)
add_subdirectory(services)

# TODO mlafroce: Agregar biblioteca utilities
add_executable(tests
	logger/LoggerTest.cpp
	main.cpp)

target_link_libraries(tests cppunit mensajero-utilities service-test rest-client ${JSONCPP_LIBRARIES})