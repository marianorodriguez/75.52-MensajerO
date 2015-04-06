project(mensajero)

add_library(services
	Connection.cpp
	CreateUserService.cpp
	EchoService.cpp
	NullService.cpp
	RestServer.cpp
	ServerThread.cpp
	ServiceFactory.cpp
	)

target_link_libraries(services mongoose)
