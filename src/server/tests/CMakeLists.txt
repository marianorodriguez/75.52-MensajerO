project(mensajero)

include_directories(${PROJECT_SOURCE_DIR}/../main)

add_subdirectory(rest-client)
add_subdirectory(services)

add_executable(tests
	main.cpp)

target_link_libraries(tests cppunit service-test rest-client)