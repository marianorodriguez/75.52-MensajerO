project(mensajero)

add_library(services
	ServiceCollection.cpp)

target_link_libraries(services mongoose)
