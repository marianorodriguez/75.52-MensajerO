project(mensajero)

add_library(services
	Connection.cpp
	ServiceCollection.cpp)

target_link_libraries(services mongoose)
