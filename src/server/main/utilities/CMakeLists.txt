project(mensajero)

add_library(mensajero-utilities
	Base64.cpp
	Date.cpp
	MD5.cpp
	Thread.cpp
	Time.cpp
	)

target_link_libraries(mensajero-utilities pthread)