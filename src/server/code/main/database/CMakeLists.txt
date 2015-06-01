project(mensajero)

add_library(mensajero-database
	Database.cpp
	IPersistible.cpp
	)

target_link_libraries(mensajero-database mensajero-utilities
					${ROCKSDB_LIBRARIES}  pthread z bz2)
