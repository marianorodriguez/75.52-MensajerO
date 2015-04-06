project(mensajero)

add_library(service-test
	RestServerTest.cpp
	ServiceFactoryTest.cpp)

target_link_libraries(service-test mensajero-services mensajero-utilities)
