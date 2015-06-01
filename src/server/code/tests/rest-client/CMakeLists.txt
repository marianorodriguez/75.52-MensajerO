project(mensajero)

add_library(rest-client
	RestClient.cpp
	RestClientTest.cpp)

target_link_libraries(rest-client curl mensajero-services)
