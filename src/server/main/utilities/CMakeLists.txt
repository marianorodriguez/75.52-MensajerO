project(mensajero)

add_library(mensajero-utilities
	base64.cpp
	Thread.cpp
	)

target_link_libraries(mensajero-utilities pthread)