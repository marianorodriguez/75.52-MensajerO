project(mensajero)

add_library(service-test
	EchoService.cpp
	ServiceCollectionTest.cpp)

target_link_libraries(service-test services)
