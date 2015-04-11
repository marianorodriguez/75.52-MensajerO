project(mensajero)

add_library(mensajero-utilities
	Base64.cpp
	Time.cpp
	Date.cpp
	MD5.cpp
	)

target_link_libraries(mensajero-utilities pthread)