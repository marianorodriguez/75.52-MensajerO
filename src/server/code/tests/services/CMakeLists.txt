project(mensajero)

add_library(service-test
	ServiceTest.cpp
	NullServiceTest.cpp
	ServerConfigTest.cpp
	EchoService.cpp
	RestServerTest.cpp
	ServiceFactoryTest.cpp
	BroadcastServiceTest.cpp
	ConnectionManagerTest.cpp
	LogInServiceTest.cpp
	SignUpServiceTest.cpp
	UserConfigServiceTest.cpp
	SomethingForMeServiceTest.cpp
	CurrentChatsServiceTest.cpp
	UsersServiceTest.cpp
	SendMessageServiceTest.cpp
	DeleteChatServiceTest.cpp)

target_link_libraries(service-test mensajero-services mensajero-utilities)