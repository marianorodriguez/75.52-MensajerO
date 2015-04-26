project(mensajero)

add_library(mensajero-services
	Connection.cpp
	NullService.cpp
	QueryParams.cpp
	RestServer.cpp
	ServerThread.cpp
	ServiceFactory.cpp
	SignUpService.cpp
	)

target_link_libraries(mensajero-services mongoose mensajero-database)
