project(mensajero)

add_library(mensajero-services
	Connection.cpp
	CurrentChatsService.cpp
	BroadcastService.cpp
	LogInService.cpp
	NullService.cpp
	RestServer.cpp
	SendMessageService.cpp
	ServerConfig.cpp
	ServerThread.cpp
	ServiceFactory.cpp
	SignUpService.cpp
	SomethingForMeService.cpp
	UserConfigService.cpp
	UsersService.cpp
	DeleteChatService.cpp
	)

target_link_libraries(mensajero-services ${JSONCPP_LIBRARIES} mongoose mensajero-database)
