project(mensajero)

add_library(mensajero-utilities
	Base64.cpp
	Date.cpp
	Logger.cpp
	JsonMap.cpp
	Mutex.cpp
	NumberConverter.cpp
	Thread.cpp
	Time.cpp
	)

target_link_libraries(mensajero-utilities mensajero-model pthread)
