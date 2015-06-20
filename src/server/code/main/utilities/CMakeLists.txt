project(mensajero)

add_library(mensajero-utilities
	Date.cpp
	Time.cpp
	Mutex.cpp
	Thread.cpp
	Base64.cpp
	Logger.cpp
	NumberConverter.cpp
	LocationManager.cpp
	ConnectionManager.cpp
	)

target_link_libraries(mensajero-utilities mensajero-model pthread)
