project(mensajero)

include_directories(${PROJECT_SOURCE_DIR}/../../include/main)
include_directories(${PROJECT_SOURCE_DIR}/../../include/tests/)

add_subdirectory(rest-client)
add_subdirectory(services)

add_executable(tests
	database/DatabaseTests.cpp
	logger/LoggerTest.cpp
	user/chat/ChatTests.cpp
	user/chat/MessageTests.cpp
	user/userTests.cpp
	ArgsParserTests.cpp
	NumberConverterTests.cpp
	services/ConnectionManagerTest.cpp
	services/LogInServiceTest.cpp
	main.cpp)

target_link_libraries(tests ${CPPUNIT_LIBRARIES} mensajero-utilities service-test rest-client ${JSONCPP_LIBRARIES})
