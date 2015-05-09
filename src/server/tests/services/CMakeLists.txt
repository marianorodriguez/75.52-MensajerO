project(mensajero)

add_library(service-test
	EchoService.cpp
	RestServerTest.cpp
	ServiceFactoryTest.cpp
	ConnectionManagerTest.cpp
	LogInServiceTest.cpp
	SignUpServiceTest.cpp
	UserConfigServiceTest.cpp)

target_link_libraries(service-test mensajero-services mensajero-utilities)
