project(mensajero)

add_library(service-test
	ServiceFactoryTest.cpp)

target_link_libraries(service-test services)
