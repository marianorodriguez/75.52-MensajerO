project(mensajero)

include_directories(${PROJECT_SOURCE_DIR}/../main)

add_subdirectory(rest-client)
add_subdirectory(services)

add_executable(tests
	database/DatabaseTests.cpp
	logger/LoggerTest.cpp
	user/userTests.cpp
	main.cpp)

target_link_libraries(tests cppunit mensajero-utilities service-test rest-client ${JSONCPP_LIBRARIES})
