project(mensajero)

add_library(service-test
	EchoService.cpp
	RestServerTest.cpp
	ServiceFactoryTest.cpp
	ConnectionManagerTest.cpp
	LogInServiceTest.cpp
	SignUpServiceTest.cpp
	UserConfigServiceTest.cpp
	SomethingForMeServiceTest.cpp
	CurrentChatsServiceTest.cpp
	UsersServiceTest.cpp
	SendMessageServiceTest.cpp)

target_link_libraries(service-test mensajero-services mensajero-utilities)