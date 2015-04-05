project(mensajero)

add_library(service-test
	ServiceCollectionTest.cpp)

target_link_libraries(service-test services)
