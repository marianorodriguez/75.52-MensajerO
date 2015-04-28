project(mensajero)

add_library(mensajero-services
	Connection.cpp
	CurrentChatsService.cpp
	LogInService.cpp
	NullService.cpp
	QueryParams.cpp
	RestServer.cpp
	SendMessageService.cpp
	ServerThread.cpp
	ServiceFactory.cpp
	SignUpService.cpp
	SomethingForMeService.cpp
	)

target_link_libraries(mensajero-services mongoose mensajero-database)
